#include <bits/stdc++.h>
using namespace std;

int n, m, p, q;
vector<int> X;

/**
 * @param insert_index 横線の挿入位置(前) (0 - m)
 * @param x 選択した縦線 (1 - n-1)
 *
 */
int maze(int insert_index, int x)
{
    bool flag = false;
    int st = p;
    for (int i = 0; i < m; i++)
    {
        int x1;
        if (i == insert_index && !flag)
        {
            x1 = x;
            i--;
            flag = true;
        }
        else
        {
            // if (X.size() > 0)
            x1 = X[i];
            // else
            //     x1 = st;
        }

        if (x1 == st)
        {
            st++;
        }
        else if (x1 == st - 1)
        {
            st--;
        }
    }
    if (insert_index == m)
    {
        if (x == st)
        {
            st++;
        }
        else if (x == st - 1)
        {
            st--;
        }
    }
    return st;
}

// void okng(bool flag)
// {
//     if (flag)
//     {
//         cout << "OK\n";
//     }
//     else
//     {
//         cout << "NG\n";
//     }
// }

int main()
{
    while (1)
    {
    start:
        cin >> n >> m >> p >> q;
        if (n == 0 && m == 0 && p == 0 && q == 0)
        {
            break;
        }
        X.clear();
        X.resize(m);
        for (int i = 0; i < m; i++)
        {
            cin >> X[i];
        }

        if (maze(-1, -1) == q)
        {
            cout << "OK\n";
            continue;
        }

        for (int i = 0; i <= m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                // cout << "i:" << i << endl; // 横線の挿入位置(前)
                // cout << "j:" << j << endl; // 選択する縦線
                // cout << maze(i, j) << endl;
                if (maze(i, j) == q)
                {
                    cout << j << " " << i << "\n";
                    goto start;
                }
            }
        }
        cout << "NG\n";
    }
}