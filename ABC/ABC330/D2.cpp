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

map<pair<int, int>, int> memo;
int combination(int n, int r)
{
    if (r == 0 || r == n)
    {
        return 1;
    }
    else
    {
        if (memo.count({n, r}))
        {
            return memo[{n, r}];
        }
        return memo[{n, r}] = combination(n - 1, r - 1) + combination(n - 1, r);
    }
}

int main()
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
    for (int i = 0; i < N; i++)
    {
        if (row_circle[i].size() < 2)
        {
            continue;
        }
        for (auto j : row_circle[i])
        {
            if (col_circle[j].size() < 2)
            {
                continue;
            }
            for (int k = 0; k < N; k++)
            {
                if (k == i)
                {
                    continue;
                }
                if (S[k][j] == 'o')
                {
                    ans += combination(row_circle[i].size() - 1, 1);
                }
            }
        }
    }

    cout << ans << endl;
}
