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
    vector ans(n, vector<int>(n, -1));
    int r = 0, c = (n - 1) / 2, k = 1;
    ans[r][c] = k;
    for (int i = 0; i < n * n - 1; i++) {
        int nr = (r - 1 + n) % n;
        int nc = (c + 1) % n;
        k++;
        if (ans[nr][nc] == -1) {
            ans[nr][nc] = k;
            r = nr;
            c = nc;
        } else {
            ans[(r + 1) % n][c] = k;
            r = (r + 1) % n;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}
