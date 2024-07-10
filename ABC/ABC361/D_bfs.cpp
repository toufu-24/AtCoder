#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long long
#define ld long double

#define int ll

// BFSを用いて最短経路を求める
int bfs(const string S, const string T) {
    queue<pair<string, int>> que;
    map<string, int> depth_map;

    que.push({S + "..", 0});
    depth_map[S + ".."] = 0;

    while (!que.empty()) {
        auto [cur, depth] = que.front();
        que.pop();

        if (cur.substr(0, T.size()) == T) {
            return depth;
        }

        int dot_idx = cur.find("..");
        assert(dot_idx != cur.size() - 1);

        for (int i = 0; i < cur.size() - 1; i++) {
            if (i == dot_idx || i == dot_idx - 1 || i == dot_idx + 1) {
                continue;
            }
            string new_cur = cur;

            // iからの2文字を..とswap
            new_cur[dot_idx] = cur[i];
            new_cur[dot_idx + 1] = cur[i + 1];
            new_cur[i] = '.';
            new_cur[i + 1] = '.';

            if (!depth_map.count(new_cur) || depth_map[new_cur] > depth + 1) {
                depth_map[new_cur] = depth + 1;
                que.push({new_cur, depth + 1});
            }
        }
    }

    return -1;
}

int32_t main() {
    int N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    if (S == T) {
        cout << 0 << endl;
        return 0;
    }

    int ans = bfs(S, T);
    cout << ans << endl;
}