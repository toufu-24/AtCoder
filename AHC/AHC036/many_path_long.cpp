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

ans_data calc_score(vector<int> A, vector<int> long_path, int lb) {
    ans_data res;
    res.A = A;
    vector<int> B(lb, -1);
    int la = A.size();
    constexpr int n = 600, t = 600 + 1;
    int score = 0;
    vector<string> ans;
    for (int i = 0; i < long_path.size(); i++) {
        if (find(all(B), long_path[i]) == B.end()) {
            // 信号操作
            res.score++;
            // 一番最後の移動なら考える必要なし
            if (i == long_path.size() - 1) {
                int idx = find(all(A), long_path[i]) - A.begin();
                res.ans.push_back("s " + string("1") + " " + to_string(idx) + " " + "0");
                for (int k = 0; k < lb; k++) {
                    B[k] = A[la - lb + k];
                }
            } else {

                // 次の場所が含まれるような区間を探す
                vector<int> now_idx;
                // 一個先が含まれるような区間を探す．最大長はlb
                vector<int> next_idx;
                const int now = long_path[i];
                const int next = long_path[i + 1];
                for (int j = 0; j < la; j++) {
                    if (A[j] == now) {
                        now_idx.push_back(j);
                    }
                    if (A[j] == next) {
                        next_idx.push_back(j);
                    }
                }
                int nearest = 1e9;
                int nearest_idx_now = -1, nearest_idx_next = -1;
                for (int j = 0; j < now_idx.size(); j++) {
                    int upp_idx = upper_bound(all(next_idx), now_idx[j]) - next_idx.begin();
                    int low_idx = upp_idx == 0 ? 0 : upp_idx - 1;
                    int nearst_idx_tmp = abs(next_idx[upp_idx] - now_idx[j]) < abs(next_idx[low_idx] - now_idx[j]) ? next_idx[upp_idx] : next_idx[low_idx];
                    if (nearest > abs(nearst_idx_tmp - now_idx[j])) {
                        nearest = abs(nearst_idx_tmp - now_idx[j]);
                        nearest_idx_now = now_idx[j];
                        nearest_idx_next = nearst_idx_tmp;
                    }
                }
                if (nearest_idx_next == -1 || nearest_idx_now == -1) {
                    nearest_idx_now = now_idx[0];
                    nearest_idx_next = now_idx[0];
                }
                int nearest_idx_left = min(nearest_idx_now, nearest_idx_next);
                int nearest_idx_right = max(nearest_idx_now, nearest_idx_next);
                int len = nearest_idx_right - nearest_idx_left + 1;
                if (len > lb) {
                    nearest_idx_left = now_idx[0];
                    if (nearest_idx_left + lb > la) {
                        nearest_idx_left = la - lb;
                    }
                    len = lb;
                }
                len = lb; // 仮に全部使ってみる
                if (nearest_idx_left + len > la) {
                    nearest_idx_left = la - len;
                }
                res.ans.push_back("s " + to_string(len) + " " + to_string(nearest_idx_left) + " " + "0");
                for (int k = 0; k < len; k++) {
                    B[k] = A[nearest_idx_left + k];
                }
            }
        }
        // 移動
        res.ans.push_back("m " + to_string(long_path[i]));
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
        // 最短経路
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
        long_path.insert(long_path.end(), all(paths[i]));
    }
    map<vector<int>, int> mp_tmp;
    for (int i = 0; i < long_path.size(); i++) {
        vector<int> tmp;
        set<int> st;
        const int init_len = 3;
        for (int j = 0; j < init_len; j++) {
            if (i + j >= long_path.size())
                break;
            if (st.contains(long_path[i + j]))
                continue;
            tmp.push_back(long_path[i + j]);
            st.insert(long_path[i + j]);
        }
        for (int j = i + init_len; j <= i + lb; j++) {
            if (j >= long_path.size())
                break;
            if (st.contains(long_path[j]))
                continue;
            tmp.push_back(long_path[j]);
            mp_tmp[tmp]++;
            st.insert(long_path[j]);
        }
    }
    set<pair<int, vector<int>>> st;
    for (auto [key, value] : mp_tmp) {
        st.insert({value, key});
    }

    // Aの初期化
    vector<int> A(la), B(lb, -1);
    set<int> unused;
    // パスに含むやつのみ必要
    for (int i = 0; i < long_path.size(); i++) {
        unused.insert(long_path[i]);
    }

    // mpを使ってAを埋める．valueが大きい順
    int cnt = 0;
    for (auto it = st.rbegin(); it != st.rend(); it++) {
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
                    assert(unused.contains(x));
                    unused.erase(x);
                }
            }
        } else {
            for (int j = 0; j < path.size(); j++) {
                if (cnt + unused.size() == la) {
                    break;
                }
                A[cnt++] = path[j];
                unused.erase(path[j]);
            }
        }
    }
    if (unused.size() > 0) {
        for (int i = 0; i < long_path.size(); i++) {
            if (unused.contains(long_path[i])) {
                A[cnt++] = long_path[i];
                unused.erase(long_path[i]);
            }
            if (cnt == la) {
                break;
            }
        }
    }

    // 移動&信号操作
    auto [score, A_, ans] = calc_score(A, long_path, lb);
    cerr << "my calc: " << score << endl;
    for (auto x : A_) {
        cout << x << " ";
    }
    cout << endl;
    for (auto x : ans) {
        cout << x << endl;
    }
}
