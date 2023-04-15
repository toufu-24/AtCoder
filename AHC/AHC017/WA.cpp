#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, M, D, K;
    cin >> N >> M >> D >> K;
    vector<int> u(M);
    vector<int> v(M);
    vector<int> w(M);
    vector<tuple<int, int, int, int>> G(M);
    for (int i = 0; i < M; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
        get<0>(G[i]) = w[i];
        get<1>(G[i]) = u[i];
        get<2>(G[i]) = v[i];
        get<3>(G[i]) = i;
    }
    vector<int> x(N);
    vector<int> y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> x[i] >> y[i];
    }
    sort(G);
    int day_min = floor(floor(M / D) / 2);
    int day_cnt = 1;
    vector<int> r(M);
    for (int i = 0; i <= ceil(M / 2); i++)
    {
        r[get<3>(G[i])] = day_cnt;
        if ((i + 1) % day_min == 0)
        {
            day_cnt++;
            if (day_cnt > D)
            {
                day_cnt = D;
            }
        }
    }
    for (int i = ceil(M / 2) + 1; i < M; i++)
    {
        r[get<3>(G[i])] = day_cnt;
        if ((i + 1) % day_min == 0)
        {
            day_cnt--;
            if (day_cnt < 1)
            {
                day_cnt = 1;
            }
        }
    }
    for (int i = 0; i < M; i++)
    {
        cout << r[i] << " ";
    }
}