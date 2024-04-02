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
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    vector<int> num(N, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < M; j++)
        {
            if (S[i][j] == 'o')
            {
                num[i] += (1 << j);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int tmp = num[i] | num[j];
            if (tmp == (1 << M) - 1)
            {
                ans++;
            }
        }
    }
    cout << ans << endl;
}
