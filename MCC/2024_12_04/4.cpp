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

const int mod = (1 << 20);

int32_t main() {
    int Q;
    cin >> Q;
    map<int, int> mp;
    set<int> st;
    while (Q--) {
        int t, x;
        cin >> t >> x;
        int ori_x = x;
        x %= mod;
        if (t == 1) {
            if (!mp.count(x)) {
                mp[x] = ori_x;
                st.insert(x);
                if (st.count((x - 1 + mod) % mod)) {
                    st.erase((x - 1 + mod) % mod);
                }
                if (st.count((x + 1) % mod)) {
                    st.erase(x);
                }
                continue;
            }
            auto itr = st.lower_bound(x);
            if (itr == st.end()) {
                itr = st.lower_bound(-1);
            }
            int idx = (*itr + 1) % mod;
            mp[idx] = ori_x;
            st.insert(idx);
            if (st.count((idx - 1 + mod) % mod)) {
                st.erase((idx - 1 + mod) % mod);
            }
            if (st.count((idx + 1) % mod)) {
                st.erase(idx);
            }
        } else {
            if (mp.count(x)) {
                cout << mp[x] << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
}
