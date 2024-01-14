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
    int sqrtN = sqrtl(N);
    int ans = 0;
    // Nまでで，桁の和がiの倍数となる数の個数を求める
    string N_str = to_string(N);
    int len = N_str.length();

    for (int i = 1; i <= sqrtN; i++)
    {
        // dp[digit][sum] := digit桁目まで見たときに，桁の和のiで割った余りがsumである数の個数
        vector<vector<int>> dp(len + 1, vector<int>(i, 0));
        for (int digit = 0; digit < len; digit++)
        {
            dp[0][0] = 0;
            int num = N_str[digit] - '0';
            for (int sum = 0; sum < i; sum++)
            {
                for (int new_digit = 0; new_digit < 10; new_digit++)
                {
                    if (new_digit > num)
                    {
                        break;
                    }
                    dp[digit + 1][(sum + new_digit) % i] += dp[digit][sum];
                }
            }
        }
        ans += dp[len][0];
    }
    cout << ans << endl;
}