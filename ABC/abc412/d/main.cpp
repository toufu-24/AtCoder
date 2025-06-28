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
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int ans = 0;
    vector<vector<bool>> matrix(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (auto j : graph[i]) {
            if (matrix[i][j]) {
                ans++;
            } else if (i == j) {
                ans++;
            } else {
                matrix[i][j] = true;
                matrix[j][i] = true;
            }
        }
    }
    int init_ans = ans;
    ans = 1e18;
    int bit = n * (n - 1) / 2;
    // vector<bool> mask(bit, false);
    int init_bit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j]) {
                init_bit |= (1 << (i * n + j));
            }
        }
    }
    int mask = (1 << bit);

    // idx から a,b を求める
    // mask[idx] = 1 なら a,b を結ぶ辺がある
    for (int i = 0; i < mask; i++) {
        int tmp = 0;
        vector<vector<int>> tmp_graph(n);
        for (int j = 0; j < bit; j++) {
            if (i & (1 << j)) {
                int a = j / n;
                int b = j % n;
                if (a == b) {
                    tmp = 1e18;
                    break;
                }
                if (matrix[a][b]) {
                    tmp++;
                }
                tmp_graph[a].push_back(b);
                tmp_graph[b].push_back(a);
            }
        }

        for (int j = 0; j < n; j++) {
            if (tmp_graph[j].size() != 2) {
                tmp = 1e18;
                break;
            }
        }
        ans = min(ans, tmp);
    }
    cout << init_ans + ans << endl;
}
