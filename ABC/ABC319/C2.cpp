#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

vector<vector<int>> c(3, vector<int>(3, 0));

// 縦・横・斜めの列にそれぞれ2個同じ数字があるかどうかを判定する
bool isOK(int x, int y, vector<vector<bool>> &isOpened)
{
    // 縦
    vector<int> tate_nums;
    for (int i = 0; i < 3; i++)
    {
        if (i == y)
            continue;
        if (isOpened[x][i] == true)
        {
            tate_nums.push_back(c[x][i]);
        }
    }
    if (tate_nums.size() == 2)
    {
        if (tate_nums[0] == tate_nums[1])
        {
            return false;
        }
    }

    // 横
    vector<int> yoko_nums;
    for (int i = 0; i < 3; i++)
    {
        if (i == x)
            continue;
        if (isOpened[i][y] == true)
        {
            yoko_nums.push_back(c[i][y]);
        }
    }
    if (yoko_nums.size() == 2)
    {
        if (yoko_nums[0] == yoko_nums[1])
        {
            return false;
        }
    }

    // 斜め
    vector<int> naname_nums;
    // 左上から右下
    if (x == y)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == x)
                continue;
            if (isOpened[i][i] == true)
            {
                naname_nums.push_back(c[i][i]);
            }
        }
        if (naname_nums.size() == 2)
        {
            if (naname_nums[0] == naname_nums[1])
            {
                return false;
            }
        }
    }
    // 右上から左下
    naname_nums.clear();
    if (x == 2 - y)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == x)
                continue;
            if (isOpened[i][2 - i] == true)
            {
                naname_nums.push_back(c[i][2 - i]);
            }
        }
        if (naname_nums.size() == 2)
        {
            if (naname_nums[0] == naname_nums[1])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> c[i][j];
        }
    }

    ld cnt = 0;
    vector<int> perm = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    sort(perm);
    do
    {
        vector<vector<bool>> isOpened(3, vector<bool>(3, false));
        bool ok = true;
        for (int i = 0; i < perm.size(); i++)
        {
            int x = perm[i] / 3;
            int y = perm[i] % 3;
            if (isOK(x, y, isOpened))
            {
                isOpened[x][y] = true;
            }
            else
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            cnt++;
        }
    } while (next_permutation(all(perm)));

    // 9! = 362880
    ld nine = 362880;
    cout << fixed << setprecision(15);
    cout << cnt / nine << endl;
}