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
    int n, d, p;
    cin >> n >> d >> p;
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    RSORT(f);
    bool ok = true;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < d; j++) {
            if (i + j >= n) break;
            sum += f[i + j];
        }
        if (sum >= p) {
            ans += p;
            i += d - 1;
        } else {
            ok = false;
            ans += sum;
            i += d - 1;
        }
    }
    cout << ans << endl;
}
