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
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    map<char, vector<int>> A;
    for (int i = 0; i < N; i++)
    {
        A[S[i]].push_back(i);
    }

    // i以降でcが初めて出てくるidx
    vector<vector<int>> next_c(N + 1, vector<int>(26, N));
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < 26; j++)
        {
            next_c[i][j] = next_c[i + 1][j];
        }
        next_c[i][S[i] - 'a'] = i;
    }

    string ans;
    int prev_idx = 0;
    for (int i = 0; i < K; i++)
    {
        // i文字目を決める
        for (int j = 0; j < 26; j++)
        {
            int idx = next_c[prev_idx][j];
            if (N - idx >= K - i)
            {
                ans += (char)('a' + j);
                prev_idx = idx + 1;
                break;
            }
        }
    }
    cout << ans << endl;
}
