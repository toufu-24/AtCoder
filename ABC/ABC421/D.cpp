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
    pair<int, int> taka, aoki;
    cin >> taka.first >> taka.second >> aoki.first >> aoki.second;
    int n, m, l;
    cin >> n >> m >> l;
    vector<pair<char, int>> taka_moves(m), aoki_moves(l);
    for (int i = 0; i < m; i++) {
        char s;
        int a;
        cin >> s >> a;
        taka_moves[i] = {s, a};
    }
    for (int i = 0; i < l; i++) {
        char t;
        int b;
        cin >> t >> b;
        aoki_moves[i] = {t, b};
    }
    // 始まりの時間
    vector<int> taka_time(m + 1, 0), aoki_time(l + 1, 0);
    for (int i = 0; i < m; i++) {
        taka_time[i + 1] = taka_time[i] + taka_moves[i].second;
    }
    for (int i = 0; i < l; i++) {
        aoki_time[i + 1] = aoki_time[i] + aoki_moves[i].second;
    }
    map<char, pair<int, pair<int, int>>> dir = {{'U', {0, {0, -1}}}, {'L', {1, {-1, 0}}}, {'D', {2, {0, 1}}}, {'R', {3, {1, 0}}}};
    // 合うのはすれ違い，交差，同じ場所で同じ方向
    int ans = 0;
    int taka_idx = 0, aoki_idx = 0;
    pair<int, int> taka_pos, aoki_pos;
    taka_pos = {taka.second, taka.first};
    aoki_pos = {aoki.second, aoki.first};
    int now_time = 0;
    while (taka_idx < m && aoki_idx < l) {
        assert(taka_idx + 1 <= m);
        assert(aoki_idx + 1 <= l);
        int next_time = min(taka_time[taka_idx + 1], aoki_time[aoki_idx + 1]);
        int diff_time = next_time - now_time;
        char taka_dir = taka_moves[taka_idx].first;
        char aoki_dir = aoki_moves[aoki_idx].first;
        pair<int, int> next_taka_pos = {taka_pos.first + dir[taka_dir].second.first * diff_time, taka_pos.second + dir[taka_dir].second.second * diff_time};
        pair<int, int> next_aoki_pos = {aoki_pos.first + dir[aoki_dir].second.first * diff_time, aoki_pos.second + dir[aoki_dir].second.second * diff_time};
        // 同じ場所で同じ方向の可能性
        if (taka_pos == aoki_pos) {
            if (taka_dir == aoki_dir) {
                ans += diff_time;
            }
        } else if (dir[taka_dir].first % 2 != dir[aoki_dir].first % 2) {
            // 交差の可能性
            // takaが縦のとき
            if (taka_dir == 'U' || taka_dir == 'D') {
                assert(aoki_dir == 'L' || aoki_dir == 'R');
                // aokiのyがはさまれてる
                if ((taka_pos.second <= aoki_pos.second && aoki_pos.second <= next_taka_pos.second) || (next_taka_pos.second <= aoki_pos.second && aoki_pos.second <= taka_pos.second)) {
                    // takaのxがはさまれてる
                    if ((aoki_pos.first <= taka_pos.first && taka_pos.first <= next_aoki_pos.first) || (next_aoki_pos.first <= taka_pos.first && taka_pos.first <= aoki_pos.first)) {
                        int x_diff = abs(aoki_pos.first - taka_pos.first);
                        int y_diff = abs(aoki_pos.second - taka_pos.second);
                        if (y_diff == x_diff) {
                            ans++;
                        }
                    }
                }
            } else if (taka_dir == 'L' || taka_dir == 'R') {
                assert(aoki_dir == 'U' || aoki_dir == 'D');
                // takaが横のとき
                // aokiのxがはさまれてる
                if ((taka_pos.first <= aoki_pos.first && aoki_pos.first <= next_taka_pos.first) || (next_taka_pos.first <= aoki_pos.first && aoki_pos.first <= taka_pos.first)) {
                    // takaのyがはさまれてる
                    if ((aoki_pos.second <= taka_pos.second && taka_pos.second <= next_aoki_pos.second) || (next_aoki_pos.second <= taka_pos.second && taka_pos.second <= aoki_pos.second)) {
                        int x_diff = abs(aoki_pos.first - taka_pos.first);
                        int y_diff = abs(aoki_pos.second - taka_pos.second);
                        if (x_diff == y_diff) {
                            ans++;
                        }
                    }
                }
            }
        } else {
            // すれ違いの可能性
            if (taka_dir != aoki_dir) {
                // 縦のとき
                if (taka_dir == 'U' || taka_dir == 'D') {
                    // xが一致
                    if (taka_pos.first == aoki_pos.first) {
                        int y_diff = taka_pos.second - aoki_pos.second;
                        bool ok = false;
                        if (y_diff < 0) {
                            if (taka_dir == 'D') {
                                assert(aoki_dir == 'U');
                                ok = true;
                            }
                        } else {
                            if (taka_dir == 'U') {
                                assert(aoki_dir == 'D');
                                ok = true;
                            }
                        }
                        if (ok) {
                            y_diff = abs(y_diff);
                            if (y_diff % 2 == 0) {
                                if (y_diff / 2 <= diff_time) {
                                    ans++;
                                }
                            }
                        }
                    }
                } else {
                    // 横の時
                    // yが一致
                    if (taka_pos.second == aoki_pos.second) {
                        int x_diff = taka_pos.first - aoki_pos.first;
                        bool ok = false;
                        if (x_diff < 0) {
                            if (taka_dir == 'R') {
                                assert(aoki_dir == 'L');
                                ok = true;
                            }
                        } else {
                            if (taka_dir == 'L') {
                                assert(aoki_dir == 'R');
                                ok = true;
                            }
                        }
                        if (ok) {
                            x_diff = abs(x_diff);
                            if (x_diff % 2 == 0) {
                                if (x_diff / 2 <= diff_time) {
                                    ans++;
                                }
                            }
                        }
                    }
                }
            }
        }
        taka_pos = next_taka_pos;
        aoki_pos = next_aoki_pos;
        if (taka_time[taka_idx + 1] == next_time) {
            taka_idx++;
        }
        if (aoki_time[aoki_idx + 1] == next_time) {
            aoki_idx++;
        }
        now_time = next_time;
    }
    cout << ans << endl;
}