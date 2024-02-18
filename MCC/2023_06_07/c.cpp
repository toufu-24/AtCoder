#include <bits/stdc++.h>

using namespace std;
#define ARRAY_SIZE 15
int main()
{
    while (1)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }
        vector<vector<bool>> window(ARRAY_SIZE * 2, vector<bool>(ARRAY_SIZE * 2, false));
        vector<vector<bool>> curtain(ARRAY_SIZE * 2, vector<bool>(ARRAY_SIZE * 2, false));
        int x_p, y_p;
        cin >> x_p >> y_p; // ひとつ目の読み込み
        x_p += ARRAY_SIZE;
        y_p += ARRAY_SIZE;
        int x_first = x_p;
        int y_first = y_p;
        window[y_p][x_p] = true;
        for (int i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            x += ARRAY_SIZE;
            y += ARRAY_SIZE;
            window[y][x] = true;
            if (x_p == x)
            {
                if (y_p < y)
                {
                    while (y_p < y)
                    {
                        window[y_p][x] = true;
                        y_p++;
                    }
                }
                else
                {
                    int tmp = y;
                    while (tmp < y_p)
                    {
                        window[tmp][x] = true;
                        tmp++;
                    }
                }
            }
            else
            { // yが一緒の時
                if (x_p < x)
                {
                    while (x_p < x)
                    {
                        window[y][x_p] = true;
                        x_p++;
                    }
                }
                else
                {
                    int tmp = x;
                    while (tmp < x_p)
                    {
                        window[y][tmp] = true;
                        tmp++;
                    }
                }
            }
            x_p = x;
            y_p = y;
        }
        if (x_p == x_first)
        {
            if (y_p < y_first)
            {
                while (y_p < y_first)
                {
                    window[y_p][x_p] = true;
                    y_p++;
                }
            }
            else
            {
                int tmp = y_first;
                while (tmp < y_p)
                {
                    window[tmp][x_p] = true;
                    tmp++;
                }
            }
        }
        else
        {
            if (x_p < x_first)
            {
                while (x_p < x_first)
                {
                    window[y_first][x_p] = true;
                    x_p++;
                }
            }
            else
            {
                int tmp = x_first;
                while (tmp < x_p)
                {
                    window[y_first][tmp] = true;
                    tmp++;
                }
            }
        }

        cin >> x_p >> y_p; // ひとつ目の読み込み
        x_p += ARRAY_SIZE;
        y_p += ARRAY_SIZE;
        x_first = x_p;
        y_first = y_p;
        curtain[y_p][x_p] = true;
        for (int i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            x += ARRAY_SIZE;
            y += ARRAY_SIZE;
            curtain[y][x] = true;
            if (x_p == x)
            {
                if (y_p < y)
                {
                    while (y_p < y - 1)
                    {
                        curtain[y_p][x] = true;
                        y_p++;
                    }
                }
                else
                {
                    int tmp = y;
                    while (tmp < y_p - 1)
                    {
                        curtain[tmp][x] = true;
                        tmp++;
                    }
                }
            }
            else
            { // yが一緒の時
                if (x_p < x)
                {
                    while (x_p < x - 1)
                    {
                        curtain[y][x_p] = true;
                        x_p++;
                    }
                }
                else
                {
                    int tmp = x;
                    while (tmp < x_p - 1)
                    {
                        curtain[y][tmp] = true;
                        tmp++;
                    }
                }
            }
            x_p = x;
            y_p = y;
        }
        if (x_p == x_first)
        {
            if (y_p < y_first)
            {
                while (y_p < y_first - 1)
                {
                    curtain[y_p][x_p] = true;
                    y_p++;
                }
            }
            else
            {
                int tmp = y_first;
                while (tmp < y_p - 1)
                {
                    curtain[tmp][x_p] = true;
                    tmp++;
                }
            }
        }
        else
        {
            if (x_p < x_first)
            {
                while (x_p < x_first - 1)
                {
                    curtain[y_first][x_p] = true;
                    x_p++;
                }
            }
            else
            {
                int tmp = x_first;
                while (tmp < x_p - 1)
                {
                    curtain[y_first][tmp] = true;
                    tmp++;
                }
            }
        }

        bool windowFlag = false;
        bool curtainFlag = false;
        for (int i = 0; i < ARRAY_SIZE * 2; i++)
        {
            for (int j = 0; j < ARRAY_SIZE * 2; j++)
            {
                if (window[i][j] && j != ARRAY_SIZE * 2 - 1 && window[i][j + 1])
                {
                    windowFlag = true;
                    continue;
                }
                if (!windowFlag && window[i][j])
                {
                    windowFlag = true;
                }
                else if (windowFlag && window[i][j])
                {
                    windowFlag = false;
                }

                if (windowFlag)
                {
                    window[i][j] = true;
                }

                if (curtain[i][j] && j != ARRAY_SIZE * 2 - 1 && curtain[i][j + 1])
                {
                    curtainFlag = true;
                    continue;
                }
                if (!curtainFlag && curtain[i][j])
                {
                    curtainFlag = true;
                }
                else if (curtainFlag && curtain[i][j])
                {
                    curtainFlag = false;
                }

                if (curtainFlag)
                {
                    curtain[i][j] = true;
                }
            }
        }

        // for (int i = 0; i < ARRAY_SIZE * 2; i++)
        // {
        //     for (int j = 0; j < ARRAY_SIZE * 2; j++)
        //     {
        //         if (curtain[i][j])
        //         {
        //             cout << "2 ";
        //         }
        //         else if (window[i][j])
        //         {
        //             cout << "1 ";
        //         }
        //         else
        //         {
        //             cout << "0 ";
        //         }
        //     }
        //     cout << endl;
        // }

        int64_t ans = 0;
        for (int i = 0; i < ARRAY_SIZE * 2; i++)
        {
            for (int j = 0; j < ARRAY_SIZE * 2; j++)
            {
                if (window[i][j] && !curtain[i][j])
                {
                    ans++;
                }
            }
        }
        cout << ans << endl;
    }
}