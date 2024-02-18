#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    ll N, A, B;
    cin >> N >> A >> B;
    ll P, Q, R, S;
    cin >> P >> Q >> R >> S;

    ll H = Q - P + 1;
    ll W = S - R + 1;
    vector<vector<char>> ans(H, vector<char>(W, '.'));
    for (ll i = max(1 - A, 1 - B); i <= min(N - A, N - B) + 1; i++)
    {
        if (A + i - P - 1 >= 0 && A + i - P - 1 < H && B + i - R - 1 >= 0 && B + i - R - 1 < W)
        {
            ans[A + i - P - 1][B + i - R - 1] = '#';
        }
    }

    for (ll i = max(1 - A, B - N); i <= min(N - A, B - 1) + 1; i++)
    {
        if (A + i - P - 1 >= 0 && A + i - P - 1 < H && B - (i - R) - 1 >= 0 && B - (i - R) - 1 < W)
        {
            ans[A + i - P - 1][B - (i - R) - 1] = '#';
        }
    }

    for (ll i = 0; i < H; i++)
    {
        for (ll j = 0; j < W; j++)
        {
            cout << ans[i][j];
        }
        cout << endl;
    }
}