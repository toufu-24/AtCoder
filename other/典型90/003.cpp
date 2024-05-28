#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
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
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }

    // 木の直径を求める
    int r = 0;
    vector<int> r_dist(N, -1);
    r_dist[r] = 0;
    queue<int> r_q;
    r_q.push(r);
    while (!r_q.empty())
    {
        int v = r_q.front();
        r_q.pop();
        for (int nv : G[v])
        {
            if (r_dist[nv] != -1)
            {
                continue;
            }
            r_dist[nv] = r_dist[v] + 1;
            r_q.push(nv);
        }
    }
    int s = max_element(all(r_dist)) - r_dist.begin();
    vector<int> s_dist(N, -1);
    s_dist[s] = 0;
    queue<int> s_q;
    s_q.push(s);
    while (!s_q.empty())
    {
        int v = s_q.front();
        s_q.pop();
        for (int nv : G[v])
        {
            if (s_dist[nv] != -1)
            {
                continue;
            }
            s_dist[nv] = s_dist[v] + 1;
            s_q.push(nv);
        }
    }
    int t = max_element(all(s_dist)) - s_dist.begin();

    // sとtの距離が直径
    int ans = s_dist[t] + 1;
    cout << ans << endl;
}
