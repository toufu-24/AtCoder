#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<vector<int>> graph;
vector<bool> visited;
int max_dist = 0;
void dfs(int now, int cost)
{
    visited[now] = true;
    for (int i = 0; i < graph[now].size(); i++)
    {
        if (graph[now][i] != -1 && !visited[i])
        {
            dfs(i, cost + graph[now][i]);
        }
    }
    max_dist = max(max_dist, cost);
    visited[now] = false;
}

int main()
{
    int N, M;
    cin >> N >> M;
    graph.resize(N, vector<int>(N, -1));
    for (int i = 0; i < M; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        A--;
        B--;
        graph[A][B] = C;
        graph[B][A] = C;
    }
    for (int i = 0; i < N; i++)
    {
        visited.resize(N, false);
        dfs(i, 0);
    }
    cout << max_dist;
}