#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int N;
        cin >> N;
        if (N == 0)
        {
            break;
        }
        vector<int> n(N - 1);
        vector<int> d(N - 1);
        map<int, pair<int, int>> mp;
        mp[0] = {0, 0};
        int x_min = 0, x_max = 0, y_min = 0, y_max = 0;
        for (int i = 0; i < N - 1; i++)
        {
            cin >> n[i] >> d[i];
            int x, y;
            switch (d[i])
            {
            case 0:
                tie(x, y) = mp[n[i]];
                mp[i + 1] = {x - 1, y};
                if (x - 1 < x_min)
                    x_min = x - 1;
                break;
            case 1:
                tie(x, y) = mp[n[i]];
                mp[i + 1] = {x, y + 1};
                if (y + 1 > y_max)
                    y_max = y + 1;
                break;
            case 2:
                tie(x, y) = mp[n[i]];
                mp[i + 1] = {x + 1, y};
                if (x + 1 > x_max)
                    x_max = x + 1;
                break;
            case 3:
                tie(x, y) = mp[n[i]];
                mp[i + 1] = {x, y - 1};
                if (y - 1 < y_min)
                    y_min = y - 1;
                break;
            }
        }
        cout << x_max - x_min + 1 << " " << y_max - y_min + 1 << '\n';
    }
}