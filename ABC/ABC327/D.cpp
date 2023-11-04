#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

signed main()
{
    int N, M;
    cin >> N >> M;
    int max_idx = 0;
    vector<int> A(M);
    for (int i = 0; i < M; i++)
    {
        cin >> A[i];
        A[i]--;
        max_idx = max(max_idx, A[i]);
    }
    vector<int> B(M);
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
        B[i]--;
        max_idx = max(max_idx, B[i]);
    }
    // A -> B　の無向グラフ
    vector<vector<int>> graph(max_idx + 1);
    for (int i = 0; i < M; i++)
    {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    vector<bool> color(max_idx + 1, false);
    vector<bool> visited(max_idx + 1, false);
    for (int t = 0; t <= max_idx; t++)
    {
        if (visited[t])
        {
            continue;
        }
        queue<pair<int, bool>> q;
        q.push({t, false});
        color[t] = true;
        while (!q.empty())
        {
            pair<int, bool> p = q.front();
            q.pop();
            int idx = p.first;
            bool c = p.second;
            for (auto next_idx : graph[idx])
            {
                if (visited[next_idx])
                {
                    if (color[next_idx] != c)
                    {
                        cout << "No" << endl;
                        return 0;
                    }
                }
                else
                {
                    visited[next_idx] = true;
                    color[next_idx] = c;
                    q.push({next_idx, !c});
                }
            }
        }
    }
    cout << "Yes" << endl;
}