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
    vector<vector<int>> x(n);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        for (int j = 0; j < l; j++) {
            int t;
            cin >> t;
            x[i].push_back(t);
        }
    }

    set<int> st;
    for (int i = 0; i < n; i++) {
        bool ok = false;
        for (int j = 0; j < x[i].size(); j++) {
            if (st.contains(x[i][j])) {
                continue;
            }
            st.insert(x[i][j]);
            ok = true;
            cout << x[i][j] << endl;
            break;
        }
        if (!ok) {
            cout << 0 << endl;
        }
    }
}
