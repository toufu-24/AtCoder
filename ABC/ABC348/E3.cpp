#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    int N;
    cin >> N;
    vector<vector<int>> G(N);
    vector<int> A(N - 1), B(N - 1);
    for (int i = 0; i < N - 1; i++)
    {
        cin >> A[i] >> B[i];
        A[i]--;
        B[i]--;
        G[B[i]].push_back(A[i]);
        G[A[i]].push_back(B[i]);
    }
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }

    int ans = 1e18;
    int idx = -1;
    for (int i = 0; i < N; i++)
    {
        if (G[i].size() == 1)
        {
            idx = i;
            break;
        }
    }

    vector<int> dist(N, -1);
    vector<int> score(N, -1);
    score[idx] = 0;
    queue<int> q;
    q.push(idx);
    dist[idx] = 0;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int to : G[now])
        {
            if (dist[to] != -1)
                continue;
            dist[to] = dist[now] + 1;
            score[to] = score[now] + C[to] * dist[to];
            q.push(to);
        }
    }
    int init_score = 0;
    for (int i = 0; i < N; i++)
    {
        assert(dist[i] != -1);
        init_score += C[i] * dist[i];
    }
    vector<int> score2(N, -1);
    score2[idx] = init_score;
    q.push(idx);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (int to : G[now])
        {
            q.push(to);
            ans = min(ans, init_score - C[now] * dist[now] + C[to] * dist[to]);
        }
    }
    cout << ans << endl;
}
