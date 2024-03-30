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
    int landSize, oilCnt;
    double e;
    cin >> landSize >> oilCnt >> e;
    vector<vector<pair<int, int>>> oil(oilCnt);
    for (int i = 0; i < oilCnt; i++)
    {
        int d;
        cin >> d;
        for (int j = 0; j < d; j++)
        {
            int x, y;
            cin >> x >> y;
            oil[i].push_back({x, y});
        }
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < landSize; i++)
    {
        for (int j = 0; j < landSize; j++)
        {
            cout << "q 1 " << i << " " << j << endl;
            int res;
            cin >> res;
            if (res != 0)
            {
                ans.push_back({i, j});
            }
        }
    }

    cout << "a " << ans.size();
    for (auto p : ans)
    {
        cout << " " << p.first << " " << p.second;
    }
    cout << endl;
    int res;
    cin >> res;
    assert(res == 1);
}
