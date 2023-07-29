#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            bool hidariue = true;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i + k >= N || j + l >= M)
                    {
                        hidariue = false;
                        break;
                    }
                    if (S[i + k][j + l] == '.')
                    {
                        hidariue = false;
                        break;
                    }
                }
            }
            if (!hidariue)
            {
                continue;
            }
            bool hidariue_white = true;
            for (int k = 0; k < 3; k++)
            {
                if (i + k >= N || j + k >= M || j + 3 >= M || i + 3 >= N)
                {
                    hidariue_white = false;
                    break;
                }
                if (S[i + k][j + 3] == '#')
                {
                    hidariue_white = false;
                    break;
                }
                if (S[i + 3][j + k] == '#')
                {
                    hidariue_white = false;
                    break;
                }
            }
            if (S[i + 3][j + 3] == '#')
            {
                hidariue_white = false;
            }
            if (!hidariue_white)
            {
                continue;
            }

            bool migisita = true;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i + k + 6 >= N || j + l + 6 >= M)
                    {
                        migisita = false;
                        break;
                    }
                    if (S[i + k + 6][j + l + 6] == '.')
                    {
                        migisita = false;
                        break;
                    }
                }
            }
            if (!migisita)
            {
                continue;
            }
            bool migisita_white = true;
            for (int k = 0; k < 3; k++)
            {
                if (i + 6 + k >= N || j + 5 >= M)
                {
                    migisita_white = false;
                    break;
                }
                if (S[i + 6 + k][j + 5] == '#')
                {
                    migisita_white = false;
                    break;
                }

                if (i + 5 >= N || j + 6 + k >= M)
                {
                    migisita_white = false;
                    break;
                }
                if (S[i + 5][j + 6 + k] == '#')
                {
                    migisita_white = false;
                    break;
                }
            }
            if (S[i + 5][j + 5] == '#')
            {
                migisita_white = false;
            }
            if (!migisita_white)
            {
                continue;
            }
            cout << i + 1 << " " << j + 1 << endl;
        }
    }
}