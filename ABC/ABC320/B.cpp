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
    string S;
    cin >> S;
    int N = S.size();
    int ans = 0;
    // 初めの文字
    for (int i = 0; i < N; i++)
    {
        // 最後の文字
        for (int j = i; j < N; j++)
        {
            bool ok = true;
            // 回文判定
            for (int k = i; k <= j; k++)
            {
                if (S[k] != S[i + j - k])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                ans = max(ans, j - i + 1);
            }
        }
    }
    cout << ans << endl;
}