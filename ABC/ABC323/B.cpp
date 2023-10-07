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
    int N;
    cin >> N;
    vector<string> S(N);
    vector<pair<int, int>> cnt(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        int o = 0;
        for (int j = 0; j < S[i].size(); j++)
        {
            if (S[i][j] == 'o')
            {
                o++;
            }
        }
        cnt[i] = {o, -(i + 1)};
    }
    SORT(cnt);
    REVERSE(cnt);
    for (int i = 0; i < N; i++)
    {
        cout << -cnt[i].second << ' ';
    }
}