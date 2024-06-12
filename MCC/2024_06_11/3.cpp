#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

vector<int> ans;
string dfs(string now)
{
    if (now.size() == 10)
    {
        return now;
    }
    for (char c = '0'; c <= '9'; c++)
    {
        if (now.back() > c)
        {
            now += c;
            ans.push_back(stoll(now));
            dfs(now);
            now.pop_back();
        }
    }
    return "";
}

int32_t main()
{
    int K;
    cin >> K;
    // 最大: 9876543210 だけど個数はそんなないかな？
    // 2^10で1024個くらい
    for (char c = '1'; c <= '9'; c++)
    {
        string now = "";
        now += c;
        ans.push_back(stoll(now));
        dfs(now);
    }
    SORT(ans);
    cout << ans[K - 1] << endl;
}
