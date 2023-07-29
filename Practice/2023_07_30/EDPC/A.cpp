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
    int N;
    cin >> N;
    vector<int> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i];
    }
    vector<int> cost(N, 1e9);
    cost[0] = 0;
    for (int i = 0; i < N; i++)
    {
        if (i + 1 >= N)
        {
            continue;
        }
        cost[i + 1] = min(cost[i + 1], cost[i] + abs(h[i + 1] - h[i]));
        if (i + 2 >= N)
        {
            continue;
        }
        cost[i + 2] = min(cost[i + 2], cost[i] + abs(h[i + 2] - h[i]));
    }
    cout << cost[N - 1] << endl;
}