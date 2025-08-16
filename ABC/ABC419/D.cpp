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
    string s, t;
    cin >> s >> t;
    vector<int> l(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    vector<int> imos(n + 1);
    for (int i = 0; i < m; i++) {
        imos[l[i]]++;
        imos[r[i] + 1]--;
    }
    for (int i = 1; i <= n; i++) {
        imos[i] += imos[i - 1];
    }

    string ans;
    for (int i = 0; i < n; i++) {
        if (imos[i] % 2 == 0) {
            ans += s[i];
        } else {
            ans += t[i];
        }
    }
    cout << ans << endl;
}
