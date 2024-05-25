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
    vector<pair<int, int>> lr(N);
    for (int i = 0; i < N; i++)
    {
        cin >> lr[i].first >> lr[i].second;
    }

    vector<pair<int, int>> querys;
    for (auto &lr : lr)
    {
        querys.push_back({lr.first, 1});
        querys.push_back({lr.second + 1, -1});
    }
    SORT(querys);

    int cur = 0;
    int ans = 0;
    for (auto &q : querys)
    {
        cur += q.second;
        if (q.second == 1)
        {
            ans += cur - 1;
        }
    }
    cout << ans << endl;
}
