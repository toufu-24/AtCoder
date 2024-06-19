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
    string T;
    cin >> N >> T;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    vector<int> prefix(N, 0);
    for (int i = 0; i < N; i++)
    {
        int idx = 0;
        for (int j = 0; j < S[i].size(); j++)
        {
            if (S[i][j] == T[idx])
            {
                idx++;
            }
        }
        prefix[i] = idx - 1;
    }

    vector<int> back(N, 0);
    for (int i = 0; i < N; i++)
    {
        int idx = T.size() - 1;
        for (int j = S[i].size() - 1; j >= 0; j--)
        {
            if (S[i][j] == T[idx])
            {
                idx--;
            }
        }
        back[i] = idx + 1;
    }

    SORT(prefix);
    SORT(back);

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(prefix), back[i] - 1) - prefix.begin();
        ans += N - idx;
    }
    cout << ans << endl;
}