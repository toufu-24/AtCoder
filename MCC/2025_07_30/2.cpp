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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int i_tmp = min(a[i], b[i]);
        ans += i_tmp;
        a[i] -= i_tmp;
        b[i] -= i_tmp;
        int i_tmp2 = min(a[i + 1], b[i]);
        ans += i_tmp2;
        a[i + 1] -= i_tmp2;
        b[i] -= i_tmp2;
    }
    cout << ans << endl;
}
