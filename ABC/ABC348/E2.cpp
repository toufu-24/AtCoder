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
    for (int i = 0; i < N; i++)
    {
        int tmp = 0;
        vector<int> dist(N, -1);
        queue<int> q;
        q.push(i);
        dist[i] = 0;
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            for (int to : G[now])
            {
                if (dist[to] != -1)
                    continue;
                dist[to] = dist[now] + 1;
                q.push(to);
            }
        }

        for (int j = 0; j < N; j++)
        {
            assert(dist[j] != -1);
            tmp += C[j] * dist[j];
        }
        ans = min(ans, tmp);
    }
    cout << ans << endl;
}
