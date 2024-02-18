#include <bits/stdc++.h>
using namespace std;

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
        map<pair<int, int>, set<pair<int, int>>> maze;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                if (i + 1 < h)
                    maze[{i, j}].insert({i + 1, j});
                if (j + 1 < w)
                    maze[{i, j}].insert({i, j + 1});
                if (i - 1 >= 0)
                    maze[{i, j}].insert({i - 1, j});
                if (j - 1 >= 0)
                    maze[{i, j}].insert({i, j - 1});
            }
        }

        int x = 0, y = 0;
        for (int i = 0; i < 2 * h - 1; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j < w - 1; j++)
                {
                    int tmp;
                    cin >> tmp;
                    if (tmp == 1)
                    {
                        if (x < h)
                        {
                            maze[{x, j}].erase({x, j + 1});
                            maze[{x, j + 1}].erase({x, j});
                        }
                    }
                }
                x++;
            }
            else
            {
                for (int j = 0; j < w; j++)
                {
                    int tmp;
                    cin >> tmp;
                    if (tmp == 1)
                    {
                        if (y < w)
                        {
                            maze[{y, j}].erase({y + 1, j});
                            maze[{y + 1, j}].erase({y, j});
                        }
                    }
                }
                y++;
            }
        }

        // for (auto qwerty : maze[{1, 0}])
        // {
        //     cerr << qwerty.first << "," << qwerty.second << " ";
        // }
        vector<vector<int>> dist(h, vector<int>(w, -1));
        dist[0][0] = 1;
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty())
        {
            auto moto = q.front();
            int moto_x, moto_y;
            tie(moto_x, moto_y) = moto;
            q.pop();
            for (auto p : maze[moto])
            {
                int x_next, y_next;
                tie(x_next, y_next) = p;
                if (dist[x_next][y_next] == -1)
                {
                    dist[x_next][y_next] = dist[moto_x][moto_y] + 1;
                    q.push({x_next, y_next});
                }
            }
        }
        if (dist[h - 1][w - 1] != -1)
        {
            cout << dist[h - 1][w - 1] << "\n";
        }
        else
        {
            cout << 0 << "\n";
        }

        // for (int i = 0; i < h; i++)
        // {
        //     for (int j = 0; j < w; j++)
        //     {
        //         cerr << dist[i][j] << " ";
        //     }
        //     cerr << "\n";
        // }
    }
}