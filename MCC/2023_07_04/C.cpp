#include <bits/stdc++.h>
using namespace std;

int main()
{
    int cnt = 0;
    while (!cin.eof())
    {
        if (cnt != 0)
        {
            cout << "\n";
        }
        cnt++;
        int x, y;
        cin >> x;
        cin >> y;
        x = abs(x);
        y = abs(y);
        // 原点
        if (x == 0 && y == 0)
        {
            cout << 0;
        }

        // 8近傍
        else if (x <= 1 && y <= 1)
        {
            cout << 1;
        }
        else if (x == 0)
        {
            if (y % 2 == 0)
            {
                cout << y;
            }
            else
            {
                cout << y + 1;
            }
        }
        else if (y == 0)
        {
            if (x % 2 == 0)
            {
                cout << x;
            }
            else
            {
                cout << x + 1;
            }
        }
        // 奇数 - 奇数
        else if (x % 2 == 1 && y % 2 == 1)
        {
            cout << x + y - 1;
        }
        // 奇数 - 偶数
        else if ((x + y) % 2 == 1)
        {
            cout << x + y;
        }
        // 偶数 - 偶数
        else
        {
            cout << x + y;
        }
    }
}