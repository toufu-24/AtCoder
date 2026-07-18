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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n - 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> b[i];
    }

    auto a_ori = a;
    int tmp = 0;
    for (int i = 1; i < n; i++) {
        if ((a[i - 1] + a[i]) % 2 != b[i - 1]) {
            a[i]++;
            tmp++;
        }
    }
    int ans = tmp;
    tmp = 1;
    a = a_ori;
    a[0]++;
    for (int i = 1; i < n; i++) {
        if ((a[i - 1] + a[i]) % 2 != b[i - 1]) {
            a[i]++;
            tmp++;
        }
    }
    ans = min(ans, tmp);
    cout << ans << endl;
}
