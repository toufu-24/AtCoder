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
    int H, W, K;
    cin >> H >> W >> K;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    int ans = 1e9;
    // 横
    for (int i = 0; i < H; i++)
    {
        if (W < K)
            break;
        int cnt = 0;
        int x_cnt = 0;
        // まず，Kまででの.の数を数える
        for (int j = 0; j < K; j++)
        {
            if (S[i][j] == '.')
            {
                cnt++;
            }
            else if (S[i][j] == 'x')
            {
                x_cnt++;
            }
        }
        if (x_cnt == 0)
            ans = min(ans, cnt);
        // その後，Wまで走査していく
        for (int j = K; j < W; j++)
        {
            assert(j - K >= 0);
            if (S[i][j - K] == '.')
            {
                cnt--;
            }
            else if (S[i][j - K] == 'x')
            {
                x_cnt--;
            }

            if (S[i][j] == '.')
            {
                cnt++;
            }
            else if (S[i][j] == 'x')
            {
                x_cnt++;
            }
            if (x_cnt == 0)
                ans = min(ans, cnt);
        }
    }

    // 縦
    for (int i = 0; i < W; i++)
    {
        if (H < K)
            break;
        int cnt = 0;
        int x_cnt = 0;
        // まず，Kまででの.の数を数える
        for (int j = 0; j < K; j++)
        {
            if (S[j][i] == '.')
            {
                cnt++;
            }
            else if (S[j][i] == 'x')
            {
                x_cnt++;
            }
        }
        if (x_cnt == 0)
            ans = min(ans, cnt);
        // その後，Wまで走査していく
        for (int j = K; j < H; j++)
        {
            if (S[j - K][i] == '.')
            {
                cnt--;
            }
            else if (S[j - K][i] == 'x')
            {
                x_cnt--;
            }

            if (S[j][i] == '.')
            {
                cnt++;
            }
            else if (S[j][i] == 'x')
            {
                x_cnt++;
            }
            if (x_cnt == 0)
                ans = min(ans, cnt);
        }
    }

    if (ans == 1e9)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}