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

bool check(vector<vector<int>> &v)
{
    int N = v.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == N / 2 && j == N / 2)
                continue;
            if (v[i][j] == -1)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int N;
    cin >> N;
    vector ans(N, vector<int>(N, -1));
    int now = 1;
    vector<pair<int, int>> d = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    SORT(d);
    do
    {
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            ans[x][y] = now++;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + d[i].first, ny = y + d[i].second;
                if (nx == N / 2 && ny == N / 2)
                    continue;
                if (0 <= nx && nx < N && 0 <= ny && ny < N && ans[nx][ny] == -1)
                {
                    q.push({nx, ny});
                    break;
                }
            }
        }

        if (check(ans))
        {
            break;
        }
        else
        {
            now = 1;
            ans.assign(N, vector<int>(N, -1));
        }
    } while (next_permutation(all(d)));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == N / 2 && j == N / 2)
                cout << 'T' << " ";
            else
                cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}