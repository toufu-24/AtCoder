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

struct ans_data {
    int score = 0;
    vector<int> A;
    vector<string> ans;
};

ans_data calc_score(vector<int> A, vector<vector<int>> paths, int lb) {
    ans_data res;
    res.A = A;
    vector<int> B(lb, -1);
    int la = A.size();
    int n = 600, t = 600 + 1;
    int score = 0;
    vector<string> ans;
    for (int i = 0; i < t - 1; i++) {
        vector<int> path = paths[i];
        for (int j = 0; j < path.size(); j++) {
            if (find(all(B), path[j]) == B.end()) {
                // 信号操作
                res.score++;
                int a_idx = find(all(A), path[j]) - A.begin();
                if (a_idx + lb > la) {
                    res.ans.push_back("s " + to_string(lb) + " " + to_string(la - lb) + " " + to_string(0));
                    for (int k = 0; k < lb; k++) {
                        B[k] = A[la - lb + k];
                    }
                } else {
                    res.ans.push_back("s " + to_string(lb) + " " + to_string(a_idx) + " " + to_string(0));
                    for (int k = 0; k < lb; k++) {
                        B[k] = A[a_idx + k];
                    }
                }
            }
            // 移動
            res.ans.push_back("m " + to_string(path[j]));
        }
    }
    return res;
}

int32_t main() {
    int _n, m, _t, la, lb;
    cin >> _n >> m >> _t >> la >> lb;
    constexpr int n = 600, t = 600 + 1;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> target(t);
    target[0] = 0;
    for (int i = 1; i < t; i++) {
        cin >> target[i];
    }

    // 信号操作の回数を最小化する
    // 移動も併せて最大1e5
    // パスの探索
    vector<vector<int>> paths(t);
    for (int i = 0; i < t - 1; i++) {
        // target[i] -> target[i+1]に移動
        queue<int> que;
        vector<int> dist(n, 1e9);
        que.push(target[i]);
        dist[target[i]] = 0;
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int u : graph[v]) {
                if (dist[u] != 1e9)
                    continue;
                dist[u] = dist[v] + 1;
                if (u == target[i + 1]) {
                    que = queue<int>();
                    break;
                }
                que.push(u);
            }
        }

        int v = target[i + 1];
        vector<int> path;
        while (v != target[i]) {
            path.push_back(v);
            for (int u : graph[v]) {
                if (dist[u] == dist[v] - 1) {
                    v = u;
                    break;
                }
            }
        }
        REVERSE(path);
        paths[i] = path;
    }
    vector<int> long_path;
    for (int i = 0; i < paths.size(); i++) {
        for (int x : paths[i]) {
            long_path.push_back(x);
        }
    }
    map<vector<int>, int> mp_tmp;
    for (int i = 0; i < long_path.size(); i++) {
        for (int j = i + 1; j < i + lb; j++) {
            vector<int> tmp;
            for (int k = i; k <= j; k++) {
                tmp.push_back(long_path[k]);
            }
            mp_tmp[tmp]++;
        }
    }
    map<int, vector<int>> mp;
    for (auto [key, value] : mp_tmp) {
        mp[value] = key;
    }

    // Aの初期化
    vector<int> A(la), B(lb, -1);
    set<int> unused;
    for (int i = 0; i < n; i++) {
        unused.insert(i);
    }
    // mpを使ってAを埋める．valueが大きい順
    int cnt = 0;
    for (auto it = mp.rbegin(); it != mp.rend(); it++) {
        vector<int> path = it->second;
        if (cnt + unused.size() == la) {
            bool all_unused = true;
            for (int x : path) {
                if (!unused.contains(x)) {
                    all_unused = false;
                    break;
                }
            }
            if (all_unused) {
                for (int x : path) {
                    A[cnt++] = x;
                    unused.erase(x);
                }
            }
            continue;
        }
        for (int j = 0; j < path.size(); j++) {
            if (cnt + unused.size() == la) {
                break;
            }
            A[cnt++] = path[j];
            unused.erase(path[j]);
        }
    }
    if (unused.size() > 0) {
        for (int x : unused) {
            assert(cnt < la);
            A[cnt++] = x;
        }
    }

    // 移動&信号操作
    auto [score, A_, ans] = calc_score(A, paths, lb);
    cerr << "my calc: " << score << endl;
    for (auto x : A_) {
        cout << x << " ";
    }
    cout << endl;
    for (auto x : ans) {
        cout << x << endl;
    }
}
