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

int N;
int fix(int x)
{
    if (x < 0)
        return 0;
    if (x >= N)
        return N - 1;
    return x;
}

int main()
{
    cin >> N;
    vector<string> S(N);
    vector<pair<int, int>> player;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'P')
            {
                player.push_back({i, j});
            }
        }
    }

    int ans = 1e9;
    queue<pair<pair<int, int>, int>> q;
    q.push
}