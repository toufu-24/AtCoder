#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main() {
    int n, x, m;
    cin >> n >> x >> m;
    vector<int> hist(m, -1);
    int idx = 0;
    vector<int> sum(1, 0);
    while (true) {
        hist[x] = idx++;
        sum.push_back(sum.back() + x);
        x *= x;
        x %= m;
        if (hist[x] != -1) {
            break;
        }
    }
    if (n <= hist[x]) {
        cout << sum[n] << endl;
        return 0;
    }
    int loo = idx - hist[x];
    int ans = sum[hist[x]];
    n -= hist[x];
    ans += (n / loo) * (sum[idx] - sum[hist[x]]);
    n %= loo;
    ans += (sum[hist[x] + n] - sum[hist[x]]);
    cout << ans << endl;
}
