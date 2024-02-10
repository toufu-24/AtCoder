#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint1000000007;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; i++)
    {
        int A, B;
        cin >> A >> B;
        A--, B--;
        G[A].push_back(B);
        G[B].push_back(A);
    }
    vector<ll> dist(N, 1e9);
    vector<mint> min_cnt(N, 0);
    min_cnt[0] = 1;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        for (auto new_v : G[now])
        {
            if (dist[new_v] == 1e9)
            {
                dist[new_v] = dist[now] + 1;
                q.push(new_v);
            }
            if (dist[new_v] == dist[now] + 1)
            {
                min_cnt[new_v] += min_cnt[now];
            }
        }
    }
    cout << min_cnt[N - 1].val() << endl;
}