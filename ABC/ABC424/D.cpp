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
    int t;
    cin >> t;
    while (t--) {
        int h, w;
        cin >> h >> w;
        vector<string> s(h);
        for (int i = 0; i < h; i++) {
            cin >> s[i];
        }
        int black_sq_cnt = 0;
        vector<vector<int>> cnt(h, vector<int>(w, 0));
        for (int i = 0; i < h - 1; i++) {
            for (int j = 0; j < w - 1; j++) {
                bool exist_white = false;
                for (int ii = 0; ii < 2; ii++) {
                    for (int jj = 0; jj < 2; jj++) {
                        int ni = i + ii;
                        int nj = j + jj;
                        if (s[ni][nj] == '.') {
                            exist_white = true;
                        }
                    }
                }
                if (!exist_white) {
                    for (int ii = 0; ii < 2; ii++) {
                        for (int jj = 0; jj < 2; jj++) {
                            int ni = i + ii;
                            int nj = j + jj;
                            if (s[ni][nj] == '.') {
                                continue;
                            }
                            cnt[ni][nj]++;
                        }
                    }
                    black_sq_cnt++;
                }
            }
        }

        int ans = 0;
        while (black_sq_cnt > 0) {
            ans++;
            int max_i = 0, max_j = 0;
            int max_val = 0;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (cnt[i][j] > max_val) {
                        max_val = cnt[i][j];
                        max_i = i;
                        max_j = j;
                    }
                }
            }
            assert(max_val > 0);
            s[max_i][max_j] = '.';

            black_sq_cnt = 0;
            cnt = vector<vector<int>>(h, vector<int>(w, 0));
            for (int i = 0; i < h - 1; i++) {
                for (int j = 0; j < w - 1; j++) {
                    bool exist_white = false;
                    for (int ii = 0; ii < 2; ii++) {
                        for (int jj = 0; jj < 2; jj++) {
                            int ni = i + ii;
                            int nj = j + jj;
                            if (s[ni][nj] == '.') {
                                exist_white = true;
                            }
                        }
                    }
                    if (!exist_white) {
                        for (int ii = 0; ii < 2; ii++) {
                            for (int jj = 0; jj < 2; jj++) {
                                int ni = i + ii;
                                int nj = j + jj;
                                if (s[ni][nj] == '.') {
                                    assert(false);
                                }
                                cnt[ni][nj]++;
                            }
                        }
                        black_sq_cnt++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}
