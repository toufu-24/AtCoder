#include <bits/stdc++.h>
using namespace std;

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> grid(H + 1, vector<char>(W + 1));
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> grid[i][j];
        }
    }
    pair<int, int> my_place;
    my_place = make_pair(1, 1);
    bool flag = false;
    while (1)
    {
        if ((double)(double(clock()) / double(CLOCKS_PER_SEC)) > 1.5)
        {
            break;
        }
        if (grid[my_place.first][my_place.second] == 'U' && my_place.first != 1)
        {
            my_place.first = my_place.first - 1;
        }
        else if (grid[my_place.first][my_place.second] == 'D' && my_place.first != H)
        {
            my_place.first = my_place.first + 1;
        }
        else if (grid[my_place.first][my_place.second] == 'L' && my_place.second != 1)
        {
            my_place.second = my_place.second - 1;
        }
        else if (grid[my_place.first][my_place.second] == 'R' && my_place.second != W)
        {
            my_place.second = my_place.second + 1;
        }
        else
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout << my_place.first << " " << my_place.second << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
}