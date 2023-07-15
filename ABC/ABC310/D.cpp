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
    int N, T, M;
    cin >> N >> T >> M;
    vector<pair<int, int>> bad(M);
    vector<bool> human(N, false);
    for (int i = 0; i < M; i++)
    {
        cin >> bad[i].first >> bad[i].second;
        bad[i].first--;
        bad[i].second--;
        human[bad[i].first] = true;
        human[bad[i].second] = true;
    }
    int bad_count = 0;
    for (int i = 0; i < N; i++)
    {
        if (human[i])
        {
            bad_count++;
        }
    }

    dsu d(N);
    for (int i = 0; i < N; i++)
    {
    }
}