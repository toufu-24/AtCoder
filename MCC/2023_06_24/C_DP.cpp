#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

int main()
{
    while (1)
    {
        ll N, D;
        cin >> N >> D;
        if (N == 0 && D == 0)
        {
            break;
        }
        vector<vector<ll>> game(N, vector<ll>(2));
        for (ll i = 0; i < N; i++)
        {
            cin >> game[i][0] >> game[i][1];
        }
    }
}