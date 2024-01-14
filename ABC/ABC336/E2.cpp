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

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    int len = to_string(N).size();
    int sqrtN = sqrtl(N);
    string N_str = to_string(N);
    int ans = 0;
    for (int i = 1; i <= sqrtN; i++)
    {
        // 桁DPを使用して、iの倍数となる数の個数を求める
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(2, vector<int>(i, 0)));
        dp[0][0][0] = 1; // 初期化

        for (int digit = 0; digit < len; digit++)
        {
            int num = N_str[digit] - '0';
            for (int less = 0; less < 2; less++)
            {
                for (int sum = 0; sum < i; sum++)
                {
                    for (int new_digit = 0; new_digit <= (less ? 9 : num); new_digit++)
                    {
                        dp[digit + 1][less || new_digit < num][(sum + new_digit) % i] += dp[digit][less][sum];
                    }
                }
            }
        }

        ans += dp[len][0][0]; // N以下の数のために、lessが0または1の場合の個数を合計する
    }

    cout << ans << endl;
}