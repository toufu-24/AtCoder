#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            break;
        }
        vector<vector<int>> p(m, vector<int>(n));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> p[i][j];
            }
        }
        vector<int> point(n, 0);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                point[j] += p[i][j];
            }
        }
        cout << *max_element(point.begin(), point.end()) << endl;
    }
}