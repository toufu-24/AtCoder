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

struct edge {
    int to;
    char label;
};

int32_t main() {
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    // i - > j を見た時のj,kにいる最短距離
    vector ans(n, vector(n, vector(n, vector(n, 1e18))));
    priority_queue<pair<int, pair<pair<int, int>, pair<int, int>>>, vector<pair<int, pair<pair<int, int>, pair<int, int>>>>, greater<pair<int, pair<pair<int, int>, pair<int, int>>>>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            q.push({0, {{i, j}, {i, j}}});
        }
    }
    vector<vector<bool>> used(n, vector(n, false));
    while (!q.empty()) {
        auto [d, p] = q.top();
        auto [sg, p2] = p;
        auto [start, goal] = sg;
        auto [a, b] = p2;
        q.pop();
        // a == b
        if (a == b) {
            if (ans[start][goal][a][a] > d) {
                ans[start][goal][a][a] = d;
                used[start][goal] = true;
            }
        }
        if (used[start][goal]) {
            continue;
        }
        // 両端を増やす
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[a][i] == '-' || s[j][b] == '-') {
                    continue;
                }
                if (s[a][i] == s[j][b]) {
                    if (ans[start][goal][i][j] > d + 2) {
                        ans[start][goal][i][j] = d + 2;
                        q.push({d + 2, {{start, goal}, {i, j}}});
                    }
                }
            }
        } 
        // 二つを結べるか
        // a -> ? -> b
        for (int i = 0; i < n; i++) {
            if (s[a][i] == '-' || s[i][b] == '-') {
                continue;
            }
            if (s[a][i] == s[i][b]) {
                if (ans[start][goal][a][a] > d + 1) {
                    ans[start][goal][a][a] = d + 1;
                }
                used[start][goal] = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = 1e18;
            for (int a = 0; a < n; a++) {
                tmp = min<long>(tmp, ans[i][j][a][a]);
            }
            if (tmp == 1e18) {
                cout << -1;
            } else {
                cout << tmp;
            }
            cout << " \n"[j == n - 1];
        }
    }
}