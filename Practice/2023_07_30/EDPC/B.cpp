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
    int N, K;
    cin >> N >> K;
    vector<int> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i];
    }
    vector<int> cost(N, 1e9);
    cost[0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (i + j >= N)
            {
                continue;
            }
            cost[i + j] = min(cost[i + j], cost[i] + abs(h[i + j] - h[i]));
        }
    }
    cout << cost[N - 1] << endl;
}