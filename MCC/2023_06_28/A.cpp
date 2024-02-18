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
        vector<vector<int>> squere(500, vector<int>(500, -1));
        map<int, pair<int, int>> mp;
        mp[0] = {250, 250};
        squere[250][250] = 0;
        for (int i = 0; i < N - 1; i++)
        {
            cin >> n[i] >> d[i];
            int x, y;
            switch (d[i])
            {
            case 0:
                tie(x, y) = mp[n[i]];
                squere[x - 1][y] = i + 1;
                mp[i + 1] = {x - 1, y};
                break;
            case 1:
                tie(x, y) = mp[n[i]];
                squere[x][y + 1] = i + 1;
                mp[i + 1] = {x, y + 1};
                break;
            case 2:
                tie(x, y) = mp[n[i]];
                squere[x + 1][y] = i + 1;
                mp[i + 1] = {x + 1, y};
                break;
            case 3:
                tie(x, y) = mp[n[i]];
                squere[x][y - 1] = i + 1;
                mp[i + 1] = {x, y - 1};
                break;
            }
        }
        int vertincal = 0;
        int horizon = 0;
        for (int i = 0; i < 500; i++)
        {
            int j;
            for (j = 0; j < 500; j++)
            {
                if (squere[i][j] != -1)
                {
                    break;
                }
            }
            for (int k = 499; k >= 0; k--)
            {
                if (j > k)
                {
                    break;
                }
                if (squere[i][k] != -1)
                {
                    int dif = k - j;
                    horizon = max(horizon, dif);
                    break;
                }
            }
        }

        for (int i = 0; i < 500; i++)
        {
            int j;
            for (j = 0; j < 500; j++)
            {
                if (squere[j][i] != -1)
                {
                    break;
                }
            }
            for (int k = 499; k >= 0; k--)
            {
                if (j > k)
                {
                    break;
                }
                if (squere[k][i] != -1)
                {
                    int dif = k - j;
                    vertincal = max(vertincal, dif);
                    break;
                }
            }
        }

        cout << vertincal + 1 << " " << horizon + 1 << "\n";
    }
}