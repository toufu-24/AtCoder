#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int y = 0; y < n; ++y)
    {
        for (int x = 0; x < n; ++x)
        {
            cin >> a[y][x];
        }
    }

    int need_distance = n / 2;

    vector<vector<set<int>>> neighbor(n, vector<set<int>>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j + 1 < n)
                neighbor[i][j].insert(a[i][j + 1]);
            if (i + 1 < n)
                neighbor[i][j].insert(a[i + 1][j]);
            if (j - 1 >= 0)
                neighbor[i][j].insert(a[i][j - 1]);
            if (i - 1 >= 0)
                neighbor[i][j].insert(a[i - 1][j]);
        }
    }

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    while (1)
    {
        int x1 = rand() % n;
        int y1 = rand() % n;
        int x2 = rand() % n;
        int y2 = rand() % n;
        bool swap_flg = true;
        swap(a[y1][x1], a[y2][x2]);
    }
}