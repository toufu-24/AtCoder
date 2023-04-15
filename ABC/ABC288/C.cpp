#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int cnt = 0;

vector<int> isPassed(101010, false);
vector<bool> iscounted(101010, false);
vector<vector<int>> graph(101010);

bool dfs(const int current, const int before)
{
    isPassed[current] = true;
    for (int i = 0; i < graph[current].size(); i++)
    {
        if (graph[current][i] == before || iscounted[graph[current][i]])
        {
            continue;
        }
        if (isPassed[graph[current][i]])
        {
            cnt++;
            iscounted[graph[current][i]] = true;
            iscounted[current] = true;
            for (auto x : graph[current])
            {
                iscounted[x] = true;
            }

            return true;
        }
        dfs(graph[current][i], current);
    }
    return false;
}

void rec(int v, vector<vector<int>> &G, vector<bool> &seen)
{
    seen[v] = true;
    for (auto v2 : G[v])
    {
        if (seen[v2])
        {
            continue;
        }
        rec(v2, G, seen);
    }
    return;
}

int main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    for (int v = 0; v < N; ++v)
    {
        dfs(0, -1);
    }
    vector<bool> seen(N, false);
    int num = 0;
    for (int v = 0; v < N; ++v)
    {
        if (seen[v])
        {
            continue;
        }
        rec(v, graph, seen);
        num++;
    }
    cnt -= num - 1;
    for (int i = 0; i < N; i++)
    {
        if (graph[i].size() == 0)
        {
            cnt++;
        }
    }

    cout << cnt;
}