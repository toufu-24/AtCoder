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

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    int ans = 1e18;
    for (int bit = 0; bit < (1 << N); bit++)
    {
        int cnt = 0;
        vector<bool> exist(M, false);
        for (int i = 0; i < N; i++)
        {
            if (bit & (1 << i))
            {
                cnt++;
                for (int j = 0; j < M; j++)
                {
                    if (S[i][j] == 'o')
                    {
                        exist[j] = true;
                    }
                }
            }
        }
        bool ok = true;
        for (int i = 0; i < M; i++)
        {
            if (!exist[i])
            {
                ok = false;
            }
        }
        if (ok)
        {
            ans = min(ans, cnt);
        }
    }
    cout << ans << endl;
}
