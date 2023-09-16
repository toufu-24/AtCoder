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

signed main()
{
    int M;
    cin >> M;
    vector<string> S(3);
    for (int i = 0; i < 3; i++)
    {
        cin >> S[i];
    }

    int ans = 1e18;
    // すべての数字について
    for (int i = 0; i <= 9; i++)
    {
        // すべての文字列について
        sort(all(S), [&](string a, string b)
             {
                 for (int j = M - 1; j >= 0; j--)
                 {
                    if (a[j] == char('0' + i))
                    {
                        return false;
                    }
                    if (b[j] == char('0' + i))
                    {
                        return true;
                    }
                 }
                 return false; });

        int maximum = 0;
        set<int> all_idx;
        bool exist = true;
        for (int j = 0; j < 3; j++)
        {
            // すべての文字について
            vector<int> idx;
            bool ok = false;
            bool exist_S = false;
            for (int k = 0; k < M; k++)
            {
                if (S[j][k] == char('0' + i))
                {
                    exist_S = true;
                    idx.push_back(k);
                    if (all_idx.count(k))
                    {
                        continue;
                    }
                    ok = true;
                    all_idx.insert(k);
                    maximum = max(maximum, k);
                    break;
                }
            }
            // 存在はするけど、すでに使われている場合
            if (exist_S && !ok)
            {
                int mini = 1e18;
                for (auto k : idx)
                {
                    while (all_idx.count(k))
                    {
                        k += M;
                    }
                    mini = min(mini, k);
                }
                ok = true;
                all_idx.insert(mini);
                maximum = max(maximum, mini);
            }
            exist &= ok;
        }
        if (exist)
        {
            ans = min(ans, maximum);
        }
    }
    if (ans == 1e18)
    {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
}