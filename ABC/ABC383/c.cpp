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
    int h, w, d;
    cin >> h >> w >> d;
    vector<string> s(h);
    queue<tuple<int, int, int>> q;
    set<pair<int, int>> humid;
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'H') {
                q.push({i, j, 0});
                humid.insert({i, j});
            }
        }
    }

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    while (!q.empty()) {
        auto [now_i, now_j, now_d] = q.front();
        q.pop();
        if (now_d == d)
            continue;
        for (int i = 0; i < 4; i++) {
            int next_i = now_i + dy[i];
            int next_j = now_j + dx[i];
            if (next_i < 0 || next_i >= h || next_j < 0 || next_j >= w)
                continue;
            if (s[next_i][next_j] == '#')
                continue;
            if (humid.count({next_i, next_j}))
                continue;
            humid.insert({next_i, next_j});
            q.push({next_i, next_j, now_d + 1});
        }
    }
    cout << humid.size() << endl;
}
