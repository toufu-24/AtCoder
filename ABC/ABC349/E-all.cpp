#pragma GCC optimize("Ofast")

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

#define int ll

int32_t main()
{
    vector<vector<int>> A(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> A[i][j];
        }
    }

    // 全パターン
    vector<int> perm(9);
    iota(all(perm), 0);
    map<vector<int>, int> win_taka;
    do
    {
        // 0-> takahashi, 1-> aoki, 2-> empty
        vector<vector<int>> board(3, vector<int>(3, 2));
        int takahashi = 0;
        int aoki = 0;
        for (int i = 0; i < 9; i++)
        {
            int x = i / 3;
            int y = i % 3;
            board[x][y] = i % 2;
            if (i % 2 == 0)
            {
                takahashi += A[x][y];
            }
            else
            {
                aoki += A[x][y];
            }
            // 3つ並んだかどうか
            for (int j = 0; j < 3; j++)
            {
                if (board[j][0] == board[j][1] && board[j][1] == board[j][2])
                {
                    if (board[j][0] == 0)
                    {
                        win_taka[perm]++;
                        goto loop;
                    }
                }
                if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
                {
                    if (board[0][j] == 0)
                    {
                        win_taka[perm]++;
                    }
                }
            }
        }
        if (takahashi > aoki)
        {
            win_taka[perm]++;
        }
    loop:;
    } while (next_permutation(all(perm)));

    bool ans = false;
    while (win_taka.size() > 1)
    {
        map<vector<int>, int> tmp;
        for (auto &&[vec, value] : win_taka)
        {
            auto vec2 = vec;
            // 高橋君のターンなら
            if (vec2.size() % 2 == 1)
            {
                vec2.pop_back();
                tmp[vec2]++;
                continue;
            }
            // 青木君のターンなら
            // 9 - vec2.size()の階乗
            int f = 1;
            for (int i = 1; i <= 9 - vec2.size(); i++)
            {
                f *= i;
            }
            if (value == f)
            {
                vec2.pop_back();
                vec2.pop_back();
                tmp[vec2] += 1;
                continue;
            }
        }
        win_taka = tmp;
        if (win_taka.size() == 1)
        {
            ans = true;
        }
    }
    cout << (ans ? "Takahashi" : "Aoki") << endl;
}
