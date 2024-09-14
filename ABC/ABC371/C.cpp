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
    int n;
    cin >> n;
    int Mg;
    cin >> Mg;
    vector<vector<int>> g(n, vector<int>(n, 0));
    for (int i = 0; i < Mg; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a][b] = 1;
        g[b][a] = 1;
    }
    int Mh;
    cin >> Mh;
    vector<vector<int>> h(n, vector<int>(n, 0));
    for (int i = 0; i < Mh; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        h[a][b] = 1;
        h[b][a] = 1;
    }
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cin >> a[i][j];
            a[j][i] = a[i][j];
        }
    }

    int ans = 1e18;
    vector<int> perm(n);
    iota(all(perm), 0);
    do {
        // permで置換
        // 実際にやってコスト計算
        int cost = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                cost += a[perm[i]][perm[j]] * (g[i][j] != h[perm[i]][perm[j]]);
            }
        }
        ans = min(ans, cost);
    } while (next_permutation(all(perm)));
    cout << ans << endl;
}
