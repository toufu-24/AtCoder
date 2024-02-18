#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int w, h;
        cin >> w >> h;
        vector<vector<int>> maze(w * 2 + 1, vector<int>(h * 2 + 1, 0));
        for (int i = 0; i < 2 * h - 1; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j < w - 1; j++)
                {
                    int tmp;
                    cin >> tmp;
                    maze[i][2 * j + 1] = tmp;
                }
            }
            else
            {
                for (int j = 0; j < w; j += 2)
                {
                    int tmp;
                    cin >> tmp;
                    maze[i][j] = tmp;
                    maze[i][j + 1] = tmp;
                }
            }
        }
    }
}