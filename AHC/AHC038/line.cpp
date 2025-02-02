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
    int n, m, v;
    cin >> n >> m >> v;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<string> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    int max_v = v;
    v = max_v;
    cout << v << endl;
    for (int i = 1; i < v; i++) {
        cout << 0 << " " << i << endl;
    }
    vector<pair<int, int>> takoyaki_pos;
    vector<pair<int, int>> takoyaki_target;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '1') {
                takoyaki_pos.push_back({i, j});
            }
            if (t[i][j] == '1') {
                takoyaki_target.push_back({i, j});
            }
        }
    }
    vector<string> ans;
    int start_x = takoyaki_pos[0].first;
    pair<int, int> hand_left = takoyaki_pos[0];
    hand_left.second -= 2;
    pair<int, int> hand_right = hand_left;
    hand_right.second += v;

    cout << hand_left.first << " " << hand_left.second << endl;

    bool go_right = true;
    bool isReverse = false;
    vector<bool> hasTakoyaki(v, false);
    int remain_takoyaki = m;
    // 順方向に進む
    while (remain_takoyaki >= m) {
        for (int i = start_x; i < n; i++) {
            if (go_right) {
                while (hand_left.second < n - 1) {
                    string move = "";
                    for (int j = 0; j < 2 * v; j++) {
                        move += ".";
                    }
                    move[0] = 'R';
                    hand_left.second++;
                    hand_right.second++;
                    for (int j = hand_left.second; j <= hand_right.second; j++) {
                        if (j < 0) {
                            continue;
                        }
                        if (j >= n) {
                            continue;
                        }
                        if (isReverse ? j == hand_right.second : j == hand_left.second) {
                            continue;
                        }
                        if (s[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == false && t[hand_left.first][j] != '1') {
                            hasTakoyaki[j - hand_left.second] = true;
                            move[(j - hand_left.second) + v] = 'P';
                            s[hand_left.first][j] = '0';
                        }
                        if (t[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == true && s[hand_left.first][j] == '0') {
                            hasTakoyaki[j - hand_left.second] = false;
                            move[j - hand_left.second + v] = 'P';
                            s[hand_left.first][j] = '1';
                            remain_takoyaki--;
                        }
                    }
                    ans.push_back(move);
                }
                go_right = false;
            } else {
                while (hand_left.second > 0) {
                    string move = "";
                    for (int j = 0; j < 2 * v; j++) {
                        move += ".";
                    }
                    move[0] = 'L';
                    hand_left.second--;
                    hand_right.second--;
                    for (int j = hand_left.second; j < hand_right.second; j++) {
                        if (j < 0) {
                            continue;
                        }
                        if (j >= n) {
                            continue;
                        }
                        if (j == hand_left.second) {
                            continue;
                        }
                        if (s[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == false && t[hand_left.first][j] != '1') {
                            hasTakoyaki[j - hand_left.second] = true;
                            move[(j - hand_left.second) + v] = 'P';
                            s[hand_left.first][j] = '0';
                        }
                        if (t[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == true && s[hand_left.first][j] == '0') {
                            hasTakoyaki[j - hand_left.second] = false;
                            move[j - hand_left.second + v] = 'P';
                            s[hand_left.first][j] = '1';
                            remain_takoyaki--;
                        }
                    }
                    ans.push_back(move);
                }

                // 180度回転
                string rotate = "";
                for (int j = 0; j <= 2 * v - 1; j++) {
                    if (1 <= j && j <= v - 1)
                        rotate += "L";
                    else
                        rotate += ".";
                }
                ans.push_back(rotate);
                rotate = "";
                for (int j = 0; j <= 2 * v - 1; j++) {
                    if (1 <= j && j <= v - 1)
                        rotate += "L";
                    else
                        rotate += ".";
                }
                ans.push_back(rotate);

                go_right = true;
                isReverse = !isReverse;
            }

            if (i == n - 1) {
                break;
            }
            if (remain_takoyaki == 0) {
                break;
            }
            string move = "D";
            for (int j = 0; j < 2 * v - 1; j++) {
                move += ".";
            }
            ans.push_back(move);
            hand_left.first++;
            hand_right.first++;
        }

        for (int i = n - 1; i >= 0; i--) {
            if (go_right) {
                while (hand_left.second < n - 1) {
                    string move = "";
                    for (int j = 0; j < 2 * v; j++) {
                        move += ".";
                    }
                    move[0] = 'R';
                    hand_left.second++;
                    hand_right.second++;
                    for (int j = hand_left.second; j < hand_right.second; j++) {
                        if (j < 0) {
                            continue;
                        }
                        if (j >= n) {
                            continue;
                        }
                        if (j == hand_left.second) {
                            continue;
                        }
                        if (s[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == false && t[hand_left.first][j] != '1') {
                            hasTakoyaki[j - hand_left.second] = true;
                            move[(j - hand_left.second) + v] = 'P';
                            s[hand_left.first][j] = '0';
                        }
                        if (t[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == true && s[hand_left.first][j] == '0') {
                            hasTakoyaki[j - hand_left.second] = false;
                            move[j - hand_left.second + v] = 'P';
                            s[hand_left.first][j] = '1';
                            remain_takoyaki--;
                        }
                    }
                    ans.push_back(move);
                }
                go_right = false;
            } else {
                while (hand_left.second > 0) {
                    string move = "";
                    for (int j = 0; j < 2 * v; j++) {
                        move += ".";
                    }
                    move[0] = 'L';
                    hand_left.second--;
                    hand_right.second--;
                    for (int j = hand_left.second; j < hand_right.second; j++) {
                        if (j < 0) {
                            continue;
                        }
                        if (j >= n) {
                            continue;
                        }
                        if (j == hand_left.second) {
                            continue;
                        }
                        if (s[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == false && t[hand_left.first][j] != '1') {
                            hasTakoyaki[j - hand_left.second] = true;
                            move[(j - hand_left.second) + v] = 'P';
                            s[hand_left.first][j] = '0';
                        }
                        if (t[hand_left.first][j] == '1' && hasTakoyaki[j - hand_left.second] == true && s[hand_left.first][j] == '0') {
                            hasTakoyaki[j - hand_left.second] = false;
                            move[j - hand_left.second + v] = 'P';
                            s[hand_left.first][j] = '1';
                            remain_takoyaki--;
                        }
                    }
                    ans.push_back(move);
                }
                go_right = true;
            }

            if (i == 0) {
                break;
            }
            if (remain_takoyaki == 0) {
                break;
            }
            string move = "U";
            for (int j = 0; j < 2 * v - 1; j++) {
                move += ".";
            }
            ans.push_back(move);
            hand_left.first--;
            hand_right.first--;
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
}
