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
    vector<vector<int>> b(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
        }
    }
    bool yoko = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (b[i][j] + 1 != b[i][j + 1]) {
                yoko = false;
                break;
            }
        }
    }
    bool tate = true;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n - 1; i++) {
            if (b[i][j] + 7 != b[i + 1][j]) {
                tate = false;
                break;
            }
        }
    }

    bool mod = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (b[i][j] % 7 == 0) {
                mod = false;
                break;
            }
        }
    }

    if (yoko && tate && mod) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
