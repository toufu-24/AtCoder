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
    vector<int> r(m), c(m);
    for (int i = 0; i < m; i++) {
        cin >> r[i] >> c[i];
    }
    set<pair<int, int>> st;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (st.contains({r[i], c[i]}) || st.contains({r[i] + 1, c[i]}) || st.contains({r[i], c[i] + 1}) || st.contains({r[i] + 1, c[i] + 1})) {
            continue;
        }
        st.insert({r[i], c[i]});
        st.insert({r[i], c[i] + 1});
        st.insert({r[i] + 1, c[i]});
        st.insert({r[i] + 1, c[i] + 1});
        ans++;
    }
    cout << ans << endl;
}
