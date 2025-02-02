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

    // 頂点数は1で固定
    cout << 1 << endl;
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

    vector<vector<int>> remove(2);
    for (int i = 0; i < takoyaki_pos.size(); i++) {
        for (int j = 0; j < takoyaki_target.size(); j++) {
            if (takoyaki_pos[i] == takoyaki_target[j]) {
                remove[0].push_back(i);
                remove[1].push_back(j);
            }
        }
    }
    RSORT(remove[0]);
    RSORT(remove[1]);
    for (int i = 0; i < remove[0].size(); i++) {
        takoyaki_pos.erase(takoyaki_pos.begin() + remove[0][i]);
    }
    for (int i = 0; i < remove[1].size(); i++) {
        takoyaki_target.erase(takoyaki_target.begin() + remove[1][i]);
    }

    // 初手はtakoyaki_pos[0]から近いとこに行く
    cout << takoyaki_pos[0].first + 1 << " " << takoyaki_pos[0].second << endl;
    pair<int, int> now = {takoyaki_pos[0].first + 1, takoyaki_pos[0].second};
    vector<string> ans;
    while (!takoyaki_target.empty()) {
        /// たこ焼きを取る
        // 一番近いやつを探す
        int min_dist = 1e9;
        int min_idx = -1;
        for (int i = 0; i < takoyaki_pos.size(); i++) {
            int dist = abs(takoyaki_pos[i].first - now.first) + abs(takoyaki_pos[i].second - now.second);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = i;
            }
        }
        // 一番近いやつに行く
        // now -> takoyaki_pos[min_idx]
        // まずは縦に行く
        for (int i = 0; i < abs(takoyaki_pos[min_idx].first - now.first); i++) {
            if (takoyaki_pos[min_idx].first > now.first) {
                ans.push_back("D.");
            } else {
                ans.push_back("U.");
            }
        }
        // 次に横に行く
        for (int i = 0; i < abs(takoyaki_pos[min_idx].second - now.second); i++) {
            if (takoyaki_pos[min_idx].second > now.second) {
                ans.push_back("R.");
            } else {
                ans.push_back("L.");
            }
        }
        // たこ焼きを取る
        ans[ans.size() - 1][1] = 'P';
        now = takoyaki_pos[min_idx];
        takoyaki_pos.erase(takoyaki_pos.begin() + min_idx);

        /// たこ焼きを置く
        // 一番近いやつを探す
        min_dist = 1e9;
        min_idx = -1;
        for (int i = 0; i < takoyaki_target.size(); i++) {
            int dist = abs(takoyaki_target[i].first - now.first) + abs(takoyaki_target[i].second - now.second);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = i;
            }
        }
        // 一番近いやつに行く
        // now -> takoyaki_target[min_idx]
        // まずは縦に行く
        for (int i = 0; i < abs(takoyaki_target[min_idx].first - now.first); i++) {
            if (takoyaki_target[min_idx].first > now.first) {
                ans.push_back("D.");
            } else {
                ans.push_back("U.");
            }
        }
        // 次に横に行く
        for (int i = 0; i < abs(takoyaki_target[min_idx].second - now.second); i++) {
            if (takoyaki_target[min_idx].second > now.second) {
                ans.push_back("R.");
            } else {
                ans.push_back("L.");
            }
        }
        // たこ焼きを置く
        ans[ans.size() - 1][1] = 'P';
        now = takoyaki_target[min_idx];
        takoyaki_target.erase(takoyaki_target.begin() + min_idx);
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << endl;
    }
}
