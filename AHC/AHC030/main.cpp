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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void output(vector<pair<int, int>> &ans)
{
    cout << "a " << ans.size();
    for (auto p : ans)
    {
        cout << " " << p.first << " " << p.second;
    }
    cout << endl;
    int res;
    cin >> res;
    if (res == 1)
    {
        exit(0);
    }
}

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

    // 固まってるはずなので，適当にサンプリングしてみる
    vector<pair<int, int>> ans;
    set<pair<int, int>> seen;
    int cnt = 0;
    for (int i = 0; i < landSize; i += 3)
    {
        for (int j = 0; j < landSize; j += 2)
        {
            if (seen.count({i, j}))
            {
                continue;
            }
            cout << "q 1 " << i << " " << j << endl;
            seen.insert({i, j});
            int res;
            cin >> res;
            if (res != 0)
            {
                ans.push_back({i, j});
                cout << "#c " << i << " " << j << " red" << endl;
                int maxRes = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                while (!q.empty())
                {
                    int x, y;
                    tie(x, y) = q.front();
                    q.pop();
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx < 0 || nx >= landSize || ny < 0 || ny >= landSize)
                        {
                            continue;
                        }
                        if (seen.count({nx, ny}))
                        {
                            continue;
                        }
                        cout << "q 1 " << nx << " " << ny << endl;
                        seen.insert({nx, ny});
                        cin >> res;
                        if (res != 0)
                        {
                            maxRes = max(maxRes, res);
                            ans.push_back({nx, ny});
                            q.push({nx, ny});
                        }
                    }
                }
                cnt += maxRes;
                if (cnt >= oilCnt)
                    output(ans);
            }
        }
    }

    output(ans);

    for (int i = 0; i < landSize; i++)
    {
        for (int j = 0; j < landSize; j++)
        {
            if (seen.count({i, j}))
            {
                continue;
            }
            cout << "q 1 " << i << " " << j << endl;
            seen.insert({i, j});
            int res;
            cin >> res;
            if (res != 0)
            {
                ans.push_back({i, j});
                cout << "#c " << i << " " << j << " red" << endl;
                int maxRes = 0;
                queue<pair<int, int>> q;
                q.push({i, j});
                while (!q.empty())
                {
                    int x, y;
                    tie(x, y) = q.front();
                    q.pop();
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx < 0 || nx >= landSize || ny < 0 || ny >= landSize)
                        {
                            continue;
                        }
                        if (seen.count({nx, ny}))
                        {
                            continue;
                        }
                        cout << "q 1 " << nx << " " << ny << endl;
                        seen.insert({nx, ny});
                        cin >> res;
                        if (res != 0)
                        {
                            maxRes = max(maxRes, res);
                            ans.push_back({nx, ny});
                            q.push({nx, ny});
                        }
                    }
                }
                cnt += maxRes;
                output(ans);
            }
        }
    }

    output(ans);
}
