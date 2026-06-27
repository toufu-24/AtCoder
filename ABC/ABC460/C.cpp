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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    SORT(a);
    SORT(b);
    multiset<int> st;
    for (auto x : b) {
        st.insert(x);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto itr = st.upper_bound(a[i] * 2);
        if (itr == st.begin()) {
            continue;
        }
        itr--;
        ans++;
        // cerr << a[i] << " " << *itr << endl;
        st.erase(itr);
        // if (st.empty()) {
        //     break;
        // }
    }
    cout << ans << endl;
}
