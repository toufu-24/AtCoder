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
    int n, d;
    cin >> n >> d;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<vector<int>> dist2(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            dist2[i][j] = dist2[j][i] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
        }
    }

    vector<bool> ans(n, false);
    ans[0] = true;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (int j = 0; j < n; j++) {
            if (dist2[i][j] <= d * d && !ans[j]) {
                ans[j] = true;
                q.push(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << (ans[i] ? "Yes" : "No") << endl;
    }
}
