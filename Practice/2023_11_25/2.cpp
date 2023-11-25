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
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        for (int j = 0; j < S[i].size(); j++)
        {
            if (S[i][j] == 'o')
            {
                cnt++;
            }
        }
        ans.push_back(make_pair(cnt, -i));
    }
    SORT(ans);
    REVERSE(ans);
    for (int i = 0; i < N; i++)
    {
        cout << -ans[i].second + 1 << " ";
    }
}