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
    int H, W, N;
    cin >> H >> W >> N;
    string T;
    cin >> T;
    vector<string> S(H);
    for (int i = 0; i < H; i++)
    {
        cin >> S[i];
    }

    set<pair<int, int>> s;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            // S[i][j]がスタート地点
            if (S[i][j] != '.')
            {
                continue;
            }

            int x = i, y = j;
            bool ok = true;
            for (int k = 0; k < T.size(); k++)
            {
                switch (T[k])
                {
                case 'L':
                    y--;
                    break;
                case 'R':
                    y++;
                    break;
                case 'U':
                    x--;
                    break;
                case 'D':
                    x++;
                    break;
                default:
                    break;
                }
                if (S[x][y] == '#')
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                s.insert({x, y});
        }
    }
    cout << s.size() << endl;
}