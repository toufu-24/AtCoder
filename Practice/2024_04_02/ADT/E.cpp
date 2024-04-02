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
    int N, K;
    cin >> N >> K;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    int ans = 0;
    for (int i = 0; i < (1 << N); i++)
    {
        vector<int> cnt(26, 0);
        for (int j = 0; j < N; j++)
        {
            if (1 & (i >> j))
            {
                for (int k = 0; k < S[j].size(); k++)
                {
                    cnt[S[j][k] - 'a']++;
                }
            }
        }
        int tmp = 0;
        for (int j = 0; j < 26; j++)
        {
            if (cnt[j] == K)
            {
                tmp++;
            }
        }
        ans = max(ans, tmp);
    }
    cout << ans << endl;
}
