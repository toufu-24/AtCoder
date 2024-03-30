#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    string N_s = to_string(N);
    int size = N_s.size();
    int cnt = 0;
    auto dfs = [&](auto &&dfs, string now) -> void
    {
        if (now.size() >= size + 1)
        {
            return;
        }
        bool seven = false, five = false, three = false;
        for (int i = 0; i < now.size(); i++)
        {
            if (now[i] == '7')
            {
                seven = true;
            }
            else if (now[i] == '5')
            {
                five = true;
            }
            else if (now[i] == '3')
            {
                three = true;
            }
        }
        if (seven && five && three && stoll(now) <= N)
        {
            cnt++;
        }
        dfs(dfs, now + "7");
        dfs(dfs, now + "5");
        dfs(dfs, now + "3");
    };
    dfs(dfs, "");
    cout << cnt << endl;
}