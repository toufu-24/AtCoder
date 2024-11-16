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

void debug(set<tuple<int, int, int>> st) {
    for (auto [l, r, c] : st) {
        for (int i = l; i <= r; i++) {
            cerr << c + 1 << " ";
        }
        cerr << "|";
    }
    cerr << endl;
}

int32_t main() {
    int n, q;
    cin >> n >> q;
    set<tuple<int, int, int>> st;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        // 閉区間で管理
        st.insert({i, i, i}); // {l, r, c}
        mp[i] = 1;
    }

    while (q--) {
        // debug(st);
        int op;
        cin >> op;
        switch (op) {
        case 1: {
            int x, c;
            cin >> x >> c;
            x--;
            c--;
            // 色をcに変更して，左右と同じ色だったらマージ
            auto it = st.upper_bound({x, 1e9, 1e9});
            if (it != st.begin()) {
                it--;
            }
            auto [itl, itr, itcolor] = *it;
            st.erase(it);
            st.insert({itl, itr, c});
            mp[itcolor] -= itr - itl + 1;
            mp[c] += itr - itl + 1;
            if (it != st.begin()) {
                it--;
                auto [l, r, color] = *it;
                if (color == c) {
                    auto itmp = it;
                    itmp++;
                    if (itmp != st.end()) {
                        auto itr2 = it;
                        itr2++;
                        auto [l2, r2, color2] = *itr2;
                        st.erase(it);
                        st.erase(itr2);
                        st.insert({l, r2, c});
                    }
                }
            }
            // debug(st);

            it = st.upper_bound({x, 1e9, 1e9});
            if (it == st.begin()) {
                break;
            }
            it--;
            auto itr2 = it;
            itr2++;
            if (itr2 != st.end()) {
                auto [l2, r2, color2] = *itr2;
                if (color2 == c) {
                    auto [l, r, color] = *it;
                    st.erase(it);
                    st.erase(itr2);
                    st.insert({l, r2, c});
                }
            }
            break;
        }
        case 2: {
            int c;
            cin >> c;
            c--;
            cout << mp[c] << endl;
            break;
        }
        }
    }
}