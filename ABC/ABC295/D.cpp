#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    string S;
    cin >> S;
    int size = S.length();
    vector<unordered_set<int>> dp(size + 1);
    int ans = 0;
    for (int i = 1; i <= size; i++)
    {
        for (int j = i; j <= size; j++)
        {
            dp[j] = dp[j - 1];
            if (dp[j].count(S[j - 1]))
            {
                dp[j].erase(S[j - 1]);
                if (dp[j].empty())
                {
                    ans++;
                }
            }
            else
            {
                dp[j].insert(S[j-1]);
            }
        }
        vector<set<int>> dp(size + 1);
    }
    cout << ans;
}