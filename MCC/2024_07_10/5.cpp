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
    int N, x, y;
    cin >> N >> x >> y;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    vector<int> yoko, tate;
    for (int i = 1; i < N; i++) {
        if (i % 2 == 0) {
            yoko.push_back(a[i]);
        } else {
            tate.push_back(a[i]);
        }
    }

    vector<vector<bool>> dp_yoko(yoko.size(), vector<bool>(2e4 + 1, false));
    dp_yoko[0][a[0] + 1e4] = true;
    for (int i = 1; i < yoko.size(); i++) {
        for (int j = 0; j < 2e4; j++) {
            if (dp_yoko[i - 1][j]) {
                if (dp_yoko[i - 1][j] + yoko[i] <= 2e4) {
                    dp_yoko[i][j + yoko[i]] = true;
                }
                if (dp_yoko[i - 1][j] - yoko[i] >= 0) {
                    dp_yoko[i][j - yoko[i]] = true;
                }
            }
        }
    }

    vector<vector<bool>> dp_tate(tate.size() + 1, vector<bool>(2e4 + 1, false));
    dp_tate[0][1e4] = true;
    for (int i = 0; i < tate.size(); i++) {
        for (int j = 0; j < 2e4; j++) {
            if (dp_tate[i][j]) {
                if (dp_tate[i][j] + tate[i] <= 2e4) {
                    dp_tate[i + 1][j + tate[i]] = true;
                }
                if (dp_tate[i][j] - tate[i] >= 0) {
                    dp_tate[i + 1][j - tate[i]] = true;
                }
            }
        }
    }

    if (dp_yoko[yoko.size() - 1][x + 1e4] && dp_tate[tate.size()][y + 1e4]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
