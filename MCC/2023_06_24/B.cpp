#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        double y, c, r;
        cin >> y >> c >> r;
        if (y == 0 && c == 0 && r == 0)
        {
            break;
        }
        // 初期値を求める
        double c_i = c, c_i_1;
        for (int i = 0; i < y - 1; i++)
        {
            c_i_1 = 100 / (100 + r) * c_i + c;
            c_i = ceil(c_i_1);
        }

        cout << int64_t(c_i) << "\n";
    }
}