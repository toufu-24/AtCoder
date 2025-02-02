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
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int oni = 2 * n, fuku = 2 * n;
    while (oni--) {
        pair<int, int> pos = {-1, -1};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i][j] == 'x') {
                    pos = {i, j};
                    break;
                }
            }
        }
        // assert(pos.first != -1);
        if (pos.first == -1) {
            break;
        }
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        vector<int> cnt_v(4, 1e9);
        vector<int> x_cnt_v(4, 0);
        for (int d = 0; d < 4; d++) {
            bool ok = true;
            int tmp = 0;
            int x_cnt = 0;
            pair<int, int> npos = {pos.first, pos.second};
            while (npos.first >= 0 && npos.first < n && npos.second >= 0 && npos.second < n) {
                if (s[npos.first][npos.second] == 'o') {
                    ok = false;
                    break;
                }
                if (s[npos.first][npos.second] == 'x') {
                    x_cnt++;
                }
                npos.first += dx[d];
                npos.second += dy[d];
                tmp++;
            }
            if (ok) {
                cnt_v[d] = tmp;
                x_cnt_v[d] = x_cnt;
            }
        }
        // cnt != 1e9 && x_cnt が最大の方向に動く
        // int cnt = *min_element(all(cnt_v));
        // int dir = min_element(all(cnt_v)) - cnt_v.begin();
        int cnt = 1e9;
        int dir = -1;
        int x_cnt = -1;
        for (int i = 0; i < 4; i++) {
            if (cnt_v[i] == 1e9)
                continue;
            if (x_cnt_v[i] > x_cnt) {
                cnt = cnt_v[i];
                dir = i;
                x_cnt = x_cnt_v[i];
            } else if (x_cnt_v[i] == x_cnt && cnt_v[i] < cnt) {
                cnt = cnt_v[i];
                dir = i;
            }
        }

        assert(dir != -1);
        if (dir == 0) {
            // 左に動く
            string new_s = s[pos.first];
            for (int i = 0; i < cnt; i++) {
                new_s = new_s.substr(1, n - 1) + ".";
                cout << 'L' << " " << pos.first << endl;
            }
            s[pos.first] = new_s;
            for (int i = 0; i < cnt; i++) {
                new_s = "." + new_s.substr(0, n - 1);
                cout << 'R' << " " << pos.first << endl;
            }
            s[pos.first] = new_s;

        } else if (dir == 1) {
            // 右に動く
            string new_s = s[pos.first];
            for (int i = 0; i < cnt; i++) {
                new_s = "." + new_s.substr(0, n - 1);
                cout << 'R' << " " << pos.first << endl;
            }
            s[pos.first] = new_s;
            for (int i = 0; i < cnt; i++) {
                new_s = new_s.substr(1, n - 1) + ".";
                cout << 'L' << " " << pos.first << endl;
            }
            s[pos.first] = new_s;
        } else if (dir == 2) {
            // 上に動く
            // pos.secondを上に動かす
            for (int i = 0; i < cnt; i++) {
                for (int j = 0; j < n - 1; j++) {
                    s[j][pos.second] = s[j + 1][pos.second];
                }
                s[n - 1][pos.second] = '.';
                cout << 'U' << " " << pos.second << endl;
            }
            for (int i = 0; i < cnt; i++) {
                for (int j = n - 1; j > 0; j--) {
                    s[j][pos.second] = s[j - 1][pos.second];
                }
                s[0][pos.second] = '.';
                cout << 'D' << " " << pos.second << endl;
            }
        } else if (dir == 3) {
            // 下に動く
            // pos.secondを下に動かす
            for (int i = 0; i < cnt; i++) {
                for (int j = n - 1; j > 0; j--) {
                    s[j][pos.second] = s[j - 1][pos.second];
                }
                s[0][pos.second] = '.';
                cout << 'D' << " " << pos.second << endl;
            }
            for (int i = 0; i < cnt; i++) {
                for (int j = 0; j < n - 1; j++) {
                    s[j][pos.second] = s[j + 1][pos.second];
                }
                s[n - 1][pos.second] = '.';
                cout << 'U' << " " << pos.second << endl;
            }
        }
    }
}
