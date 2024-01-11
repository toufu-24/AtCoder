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

int N, M;
int ans = 0;
vector<int> A;
vector<vector<int>> G;

int32_t main()
{
    cin >> N >> M;
    A.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    G.resize(N);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<bool> visited(N, false);
    priority_queue<tuple<int, int, int, vector<bool>>, vector<tuple<int, int, int, vector<bool>>>, greater<tuple<int, int, int, vector<bool>>>> q;
    q.push({A[0], 0, 1, visited});
    while (!q.empty())
    {
        auto [a, v, k, visited] = q.top();
        q.pop();
        if (v == N - 1)
        {
            ans = max(ans, k);
            continue;
        }
        visited[v] = true;
        for (int nv : G[v])
        {
            if (visited[nv])
            {
                continue;
            }
            if (A[nv] < A[v])
            {
                continue;
            }
            if (A[nv] > A[N - 1])
            {
                continue;
            }
            if (A[nv] == A[v])
            {
                q.push({A[nv], nv, k, visited});
                continue;
            }
            q.push({A[nv], nv, k + 1, visited});
        }
    }

    cout << ans << endl;
}