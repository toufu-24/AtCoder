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
    int N;
    cin >> N;
    vector<vector<vector<int>>> A(N, vector<vector<int>>(N, vector<int>(N)));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                cin >> A[i][j][k];
            }
        }
    }
    // 3次元累積和
    vector<vector<vector<int>>> cum(N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 0)));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                cum[i][j][k] = A[i - 1][j - 1][k - 1] + cum[i - 1][j][k] + cum[i][j - 1][k] + cum[i][j][k - 1] - cum[i - 1][j - 1][k] - cum[i - 1][j][k - 1] - cum[i][j - 1][k - 1] + cum[i - 1][j - 1][k - 1];
            }
        }
    }

    auto query = [&](int x1, int y1, int z1, int x2, int y2, int z2) {
        return cum[x2][y2][z2] - cum[x1 - 1][y2][z2] - cum[x2][y1 - 1][z2] - cum[x2][y2][z1 - 1] + cum[x1 - 1][y1 - 1][z2] + cum[x1 - 1][y2][z1 - 1] + cum[x2][y1 - 1][z1 - 1] - cum[x1 - 1][y1 - 1][z1 - 1];
    };

    int Q;
    cin >> Q;
    while (Q--) {
        int x1, x2, y1, y2, z1, z2;
        cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
        cout << query(x1, y1, z1, x2, y2, z2) << endl;
    }
}
