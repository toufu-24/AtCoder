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

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int cnt = 0;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; i++)
    {
        // 連結成分の個数を数える
        if (visited[i])
        {
            continue;
        }
        visited[i] = true;
        int size = 1;
        queue<int> q;
        q.push(i);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int u : graph[v])
            {
                if (visited[u])
                {
                    continue;
                }
                visited[u] = true;
                size++;
                q.push(u);
            }
        }
        // 1 から size - 2までの和
        if (size < 3)
        {
            continue;
        }
        int tmp = (size - 1) * (size - 2) / 2;
        cnt += tmp;
    }

    cout << cnt << endl;
}
