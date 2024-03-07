#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<vector<int>> graph(2 * N + 2);
    for (int i = 0; i < N; i++)
    {
        int idx = i + 1;
        graph[A[i]].push_back(2 * idx);
        graph[A[i]].push_back(2 * idx + 1);
    }

    vector<int> dist(2 * N + 2, -1);
    queue<int> q;
    q.push(1);
    dist[0] = 0;
    dist[1] = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u : graph[v])
        {
            if (dist[u] != -1)
            {
                continue;
            }
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }

    for (int i = 1; i <= 2 * N + 1; i++)
    {
        cout << dist[i] << endl;
    }
}