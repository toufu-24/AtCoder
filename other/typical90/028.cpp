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
    vector<vector<int>> paper(1002, vector<int>(1002, 0));
    for (int i = 0; i < N; i++)
    {
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        // rx++, ry++;
        paper[lx][ly]++;
        paper[rx][ry]++;
        paper[lx][ry]--;
        paper[rx][ly]--;
    }

    // 横方向に累積和
    for (int i = 0; i < 1002; i++)
    {
        for (int j = 1; j < 1002; j++)
        {
            paper[i][j] += paper[i][j - 1];
        }
    }
    // 縦方向に累積和
    for (int i = 1; i < 1002; i++)
    {
        for (int j = 0; j < 1002; j++)
        {
            paper[i][j] += paper[i - 1][j];
        }
    }

    vector<int> ans(N + 1, 0);
    for (int i = 0; i < 1002; i++)
    {
        for (int j = 0; j < 1002; j++)
        {
            ans[paper[i][j]] += 1;
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << endl;
    }
}
