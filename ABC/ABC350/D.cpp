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
    for (int i = 0; i < N; i++)
    {
        set<int> friends;
        friends.insert(all(graph[i]));
        friends.insert(i);
        queue<int> q;
        for (int f : graph[i])
        {
            q.push(f);
        }
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int u : graph[v])
            {
                if (friends.count(u))
                {
                    continue;
                }
                friends.insert(u);
                graph[i].push_back(u);
                graph[u].push_back(i);
                q.push(u);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}
