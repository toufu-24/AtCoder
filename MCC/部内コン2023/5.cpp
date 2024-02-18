#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

char TUAT[] = "TUAT";

int main()
{
    int X, A, B;
    cin >> X >> A >> B;
    string T;
    cin >> T;
    string TUAT_str;
    for (int i = 0; i < T.size(); i++)
    {
        if (T[i] == 'T' || T[i] == 'U' || T[i] == 'A')
        {
            TUAT_str += T[i];
        }
    }
    T = TUAT_str;
    // Biggining,Easyのみ
    vector<vector<int>> dp(T.size() + 1, vector<int>(4, 0));
    int ans = 0;
    for (int i = 1; i <= T.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (T[i - 1] == TUAT[j])
            {
                dp[i + 1][j] = dp[i][j];
                if (j == 0)
                {
                    dp[i + 1][j]++;
                }
                else
                {
                    dp[i + 1][j] = dp[i][j - 1] + 1;
                }
            }
            else
            {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    ans = dp[T.size()][3];
    cout << ans << endl;
}