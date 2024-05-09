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

int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
vector<pair<int, int>> next(pair<int, int> pos)
{
    auto [x, y] = pos;
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
        string tmp;
        cin >> tmp;
        for (int j = 0; j < N; j++)
        {
            A[i][j] = tmp[j] - '0';
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
                for (int d = 0; d < 8; d++)
                {
                    int x = i, y = j;
                    string num = to_string(A[x][y]);
                    for (int cnt = 0; cnt < N - 1; cnt++)
                    {
                        int nx = modint(x + dx[d]).val();
                        int ny = modint(y + dy[d]).val();
                        num += to_string(A[nx][ny]);
                        x = nx;
                        y = ny;
                    }
                    ans = max(ans, stol(num));
                }
            }
        }
    }
    cout << ans << endl;
}
