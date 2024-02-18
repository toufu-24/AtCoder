#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        int N, M;
        cin >> N >> M;
        if (N == 0 && M == 0)
        {
            break;
        }
        vector<vector<int>> a(N, vector<int>(M));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cin >> a[i][j];
            }
        }

        for (int i = 0; i < M; i++)
        {
            // aをi番目の列に対してソート
            vector<pair<int, int>> sortee(N);
            for (int j = 0; j < N; j++)
            {
                sortee[j] = {a[j][i], j};
            }
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                cerr << a[i][j];
            }
            cerr << "\n";
        }
    }
}