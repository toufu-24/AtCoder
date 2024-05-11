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
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    SORT(S);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int cnt = 0;
            for (int k = 0; k < min(S[i].size(), S[j].size()); k++)
            {
                if (S[i][k] == S[j][k])
                {
                    cnt++;
                }
                else
                {
                    break;
                }
            }
            ans += cnt;
        }
    }
    cout << ans << endl;
}
