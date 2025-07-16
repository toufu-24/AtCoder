#include <bits/stdc++.h>
using namespace std;

int pow2(int x) {
    return x * x;
}

// 本来ルートをつけるが，ルートをつけると誤差が生じるため，平方根を取らない
int calc_dist(pair<int, int> a, pair<int, int> b) {
    return pow2(a.first - b.first) + pow2(a.second - b.second);
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> people(n);
    for (int i = 0; i < n; i++) {
        cin >> people[i].first >> people[i].second;
    }

    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        // i さんについて距離が D 以内にいる人を探す
        for (int j = i + 1; j < n; j++) {
            int dist = calc_dist(people[i], people[j]);
            // 距離が D 以内ならグラフに追加 (distは2乗しているため，d*dと比較)
            if (dist <= d * d) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    // 感染者の初期化
    // 感染をtrue, 未感染をfalseとする
    vector<bool> is_infected(n, false);
    is_infected[0] = true;

    // 感染者のBFS
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto next : graph[now]) {
            if (is_infected[next]) {
                continue;
            }
            is_infected[next] = true;
            q.push(next);
        }
    }

    // 出力
    for (auto x : is_infected) {
        if (x) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
