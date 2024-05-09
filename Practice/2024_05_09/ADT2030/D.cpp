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

vector<pair<int, int>> next(pair<int, int> pos)
{
    auto [x, y] = pos;
    int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    vector<pair<int, int>> res;
    for (int i = 0; i < 8; i++)
    {
        res.push_back({modint(x + dx[i]).val(), modint(y + dy[i]).val()});
    }
    return res;
}

int32_t main()
{
    int N;
    cin >> N;
    modint::set_mod(N);
    vector<vector<int>> A(N, vector<int>(N));
    int biggest = -1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
            biggest = max(biggest, A[i][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == biggest)
            {
                // queue<pair<int, int>> q;
                queue<tuple<int, int, int>> q;
                q.push({i, j, 0});
                while (!q.empty())
                {
                    auto [x, y, depth] = q.front();
                    q.pop();
                    if (depth > ans)
                    {
                        ans = depth;
                    }
                    pair<int, int> max_pos;
                    int max_val = -1;
                    for (auto [nx, ny] : next({x, y}))
                    {
                        if (A[nx][ny] > max_val)
                        {
                            max_val = A[nx][ny];
                            max_pos = {nx, ny};
                        }
                    }

                    for (auto [nx, ny] : next({x, y}))
                    {
                        if (A[nx][ny] == max_val)
                        {
                            q.push({nx, ny, depth + 1});
                        }
                    }
                }
            }
        }
    }
}
