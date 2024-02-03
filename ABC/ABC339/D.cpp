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

int N;
int fix(int x)
{
    if (x < 0)
        return 0;
    if (x >= N)
        return N - 1;
    return x;
}

int main()
{
    cin >> N;
    vector<string> S(N);
    vector<pair<int, int>> player;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        for (int j = 0; j < N; j++)
        {
            if (S[i][j] == 'P')
            {
                player.push_back({i, j});
            }
        }
    }

    int ans = 1e9;
    vector<pair<int, int>> d = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    SORT(d);
    do
    {
        pair<int, int> play1 = player[0];
        pair<int, int> play2 = player[1];
        int now = 0;
        for (int idx = 0; idx < 4; idx++)
        {
            while (true)
            {
                int nx1 = fix(play1.first + d[idx].first);
                int ny1 = fix(play1.second + d[idx].second);
                if (S[nx1][ny1] == '#')
                {
                    nx1 = play1.first;
                    ny1 = play1.second;
                }
                int nx2 = fix(play2.first + d[idx].first);
                int ny2 = fix(play2.second + d[idx].second);
                if (S[nx2][ny2] == '#')
                {
                    nx2 = play2.first;
                    ny2 = play2.second;
                }

                if (nx1 == nx2 && ny1 == ny2)
                {
                    ans = min(ans, now);
                    goto loop;
                }
                now++;
                if (play1 == make_pair(nx1, ny1) && play2 == make_pair(nx2, ny2))
                {
                    break;
                }
                play1 = {nx1, ny1};
                play2 = {nx2, ny2};
            }
        }
    loop:;
    } while (next_permutation(all(d)));

    if (ans == 1e9)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << ans << endl;
    }
}