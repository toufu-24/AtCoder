#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    while (1)
    {
        int w, h;
        cin >> w >> h;
        if (w == 0 && h == 0)
        {
            break;
        }
        int k = w + h - 1;

        // 100マスの
        // vector<vector<int>> map(w, vector<int>(h, INT32_MAX));
        vector<vector<bool>> map(w, vector<bool>(h, false));
        // x座標，y座標，値
        vector<vector<int>> num(k, vector<int>(3));
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> num[i][j];
            }
            map[--num[i][0]][--num[i][1]] = true;
            // b_map[num[i][0]][num[i][1]] = true;
        }
        vector<bool> vertical(w, false);
        vector<bool> horizon(h, false);
        vertical[0] = true;
        while (1)
        {
            bool flag = false;
            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    if (map[i][j] && vertical[i] && !horizon[j])
                    {
                        horizon[j] = true;
                        flag = true;
                    }
                    else if (map[i][j] && !vertical[i] && horizon[j])
                    {
                        vertical[i] = true;
                        flag = true;
                    }
                }
            }
            if (!flag)
            {
                break;
            }
        }
        bool ans = true;
        for (int i = 0; i < w; i++)
        {
            if (!vertical[i])
            {
                ans = false;
                break;
            }
        }
        for (int j = 0; j < h; j++)
        {
            if (!horizon[j])
            {
                ans = false;
                break;
            }
        }
        if (ans)
        {
            cout << "YES"
                 << "\n";
        }
        else
        {
            cout << "NO"
                 << "\n";
        }
    }
}