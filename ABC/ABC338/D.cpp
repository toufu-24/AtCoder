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

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> X(M);
    for (int i = 0; i < M; i++)
    {
        cin >> X[i];
    }

    int ans = 1e9;
    // 一番長いやつだけ逆転するような辺を選ぶ
    int max_dist = 0;
    int max_idx = 0;
    vector<int> dist(M - 1);
    for (int i = 0; i < M - 1; i++)
    {
        dist[i] = abs(X[i + 1] - X[i]);
        dist[i] = min(abs(N - X[i + 1] + X[i]), dist[i]);
        if (dist[i] > max_dist)
        {
            max_dist = dist[i];
            max_idx = i;
        }
    }

    dist[max_idx] = abs(X[max_idx + 1] - X[max_idx]);
    dist[max_idx] = max(abs(N - X[max_idx + 1] + X[max_idx]), dist[max_idx]);
    cout << accumulate(all(dist), 0) << endl;
}