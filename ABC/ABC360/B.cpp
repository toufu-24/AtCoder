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

// テストケース : |T| <= |S| WA
// 書いてあった : |T| <  |S| AC
// |T| = |S| の場合も考慮する
int32_t main()
{
    string S, T;
    cin >> S >> T;
    for (int w = 1; w < S.size(); w++)
    {
        vector<string> sub;
        for (int i = 0; i < S.size(); i++)
        {
            if (i + w > S.size())
            {
                sub.push_back(S.substr(i, S.size() - i));
                break;
            }
            sub.push_back(S.substr(i, w));
            i += w - 1;
        }

        for (int c = 0; c < w; c++)
        {
            string tmp;
            for (int i = 0; i < sub.size(); i++)
            {
                if (c >= sub[i].size())
                {
                    continue;
                }
                tmp += sub[i][c];
            }
            if (tmp == T)
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}
