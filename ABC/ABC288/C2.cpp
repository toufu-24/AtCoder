#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int cnt = 0;

void dfs(int v, vector<vector<int>> &G, vector<bool> &seen, vector<bool> &finished)
{
    seen[v] = true;
    bool flag = true;
    for (auto v2 : G[v])
    {
        if (seen[v2])
        {
            if (!finished[v2])
            {
                cnt++;
                for (auto x : G[v])
                {
                    seen[x] = true;
                    finished[x] = true;
                }
            }
            if (flag && v2 != v)
            {
                cnt--;
            }
            flag = false;
            continue;
        }
        dfs(v2, G, seen, finished);
    }
    finished[v] = true;
    return;
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
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }
    vector<bool> seen(N, false);
    vector<bool> finished(N, false);
    for (int v = 0; v < N; ++v)
    {
        if (seen[v])
        {
            continue;
        }
        dfs(v, G, seen, finished);
    }
    cout << -1 * cnt;
}