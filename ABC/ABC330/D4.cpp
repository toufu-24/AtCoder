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
    int N;
    cin >> N;
    vector<string> S(N);
    vector<pair<int, int>> circle;
    vector<vector<int>> row_circle(N);
    vector<vector<int>> col_circle(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'o')
            {
                circle.push_back({i, j});
                row_circle[i].push_back(j);
                col_circle[j].push_back(i);
            }
        }
    }
    int ans = 0;
    for (auto c : circle)
    {
        int row_count = row_circle[c.first].size();
        int col_count = col_circle[c.second].size();
        ans += (row_count - 1) * (col_count - 1);
    }

    cout << ans << endl;
}
