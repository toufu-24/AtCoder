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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    set<vector<string>> st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool flag = false;
            vector<string> tmp(m);
            for (int ii = 0; ii < m; ii++) {
                for (int jj = 0; jj < m; jj++) {
                    if (i + ii >= n || j + jj >= n) {
                        flag = true;
                        break;
                    }
                    tmp[ii] += s[i + ii][j + jj];
                }
                if (flag) {
                    break;
                }
            }

            if (flag) {
                continue;
            } else {
                st.insert(tmp);
            }
        }
    }
    cout << st.size() << endl;
}
