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
    dsu d(N);
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        d.merge(u, v);
    }
    bool ok = true;
    int two = 0;
    int one = 0;
    for (int i = 0; i < N; i++)
    {
        if (graph[i].size() == 2)
        {
            two++;
        }
        else if (graph[i].size() == 1)
        {
            one++;
        }
        else
        {
            ok = false;
        }
    }
    if (!(two == N - 2 && one == 2))
    {
        ok = false;
    }
    if (d.size(0) != N)
    {
        ok = false;
    }
    if (M != N - 1)
    {
        ok = false;
    }
    if (ok)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}