#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    dist[0][0] = 0;
    int M;
    cin >> M;
    map<pair<int, int>, vector<pair<int, int>>> graph;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int l = 0; l < N; l++)
            {
                int k = i - sqrt(M - pow((l - j), 2));
                if (k >= 0 && k < N && M == pow((k - i), 2) + pow((l - j), 2))
                {
                    graph[{i, j}].push_back({k, l});
                    graph[{k, l}].push_back({i, j});
                }
            }
        }
    }
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        auto now = q.front();
        q.pop();
        for (auto next : graph[now])
        {
            if (dist[next.first][next.second] == -1)
            {
                dist[next.first][next.second] = dist[now.first][now.second] + 1;
                q.push(next);
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}