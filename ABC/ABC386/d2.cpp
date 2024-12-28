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
    vector<int> X(m), Y(m);
    vector<char> C(m);
    vector<tuple<int, int, char>> v;
    for (int i = 0; i < m; i++) {
        cin >> X[i] >> Y[i] >> C[i];
        v.push_back({X[i], Y[i], C[i]});
    }
    map<int, int> column, row;
    for (int i = 0; i < m; i++) {
        if (C[i] == 'B') {
            column[X[i]] = max(column[X[i]], Y[i]);
            row[Y[i]] = max(row[Y[i]], X[i]);
        }
    }
    bool ans = true;
    for (int i = 0; i < m; i++) {
        if (C[i] == 'W') {
            if (column.count(X[i]) && column[X[i]] >= Y[i]) {
                ans = false;
                break;
            }
            if (row.count(Y[i]) && row[Y[i]] >= X[i]) {
                ans = false;
                break;
            }
        }
    }
    cout << (ans ? "Yes" : "No") << endl;
}
