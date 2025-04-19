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
    vector<vector<int>> a(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    set<int> b_st;
    for (int i = 0; i < n; i++) {
        b_st.insert(b[i]);
    }

    map<int, int> convert;
    for (int i = 0; i < n; i++) {
        convert[b[i]] = i;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < a[i].size(); j++) {
            a[i][j] = convert[a[i][j]];
        }
    }
    vector<int> ans(n, 0);
    for (int i = 0; i < m; i++) {
        ans[*max_element(all(a[i]))]++;
    }

    for (int i = 1; i < n; i++) {
        ans[i] += ans[i - 1];
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}
