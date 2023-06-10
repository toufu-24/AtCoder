#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> graph(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<pair<int, int>> police(K);
    for (int i = 0; i < K; i++)
    {
        int c, d;
        cin >> c >> d;
        police[i] = make_pair(c, d);
    }

    vector<int> ans;
    for (int i = 0; i < K; i++)
    {
        queue<pair<int, int>> q;
        ans.push_back(police[i].first);
        q.push(make_pair(police[i].first, 0));
        int limit_depth = police[i].second;
        int cnt = 0;
        // limit_distだけBFSする
        while (!q.empty())
        {
            int now = q.front().first;
            int depth = q.front().second;
            q.pop();
            if (depth == limit_depth) // 深さ制限に達したら探索を終了する
                break;
            for (int j = 0; j < graph[now].size(); j++)
            {
                int next = graph[now][j];
                ans.push_back(next);
                q.push(make_pair(next, depth + 1));
            }
        }
    }
    sort(ans);
    ans.erase(unique(all(ans)), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}