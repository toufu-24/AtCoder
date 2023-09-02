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
    vector<vector<int>> graph(N, vector<int>(N, -1));
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            cin >> graph[i][j];
            graph[j][i] = graph[i][j];
            edges.push_back({graph[i][j], {i, j}});
        }
    }
    sort(edges);
    reverse(edges);
    int ans = 0;
    vector<bool> already(N, false);
    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i].second.first;
        int b = edges[i].second.second;
        if (already[a] || already[b])
        {
            continue;
        }
        else
        {
            ans += edges[i].first;
            already[a] = true;
            already[b] = true;
        }
    }
    cout << ans;
}