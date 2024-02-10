#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<char>> A(2 * N, vector<char>(M));
    for (int i = 0; i < 2 * N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> A[i][j];
        }
    }
    vector<pair<int, int>> won(2 * N);
    for (int i = 0; i < 2 * N; i++)
    {
        won[i] = {0, -i};
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < 2 * N; j += 2)
        {
            int a = -won[j].second, b = -won[j + 1].second;
            if (A[a][i] == 'G' && A[b][i] == 'C')
            {
                won[j].first++;
            }
            else if (A[a][i] == 'C' && A[b][i] == 'P')
            {
                won[j].first++;
            }
            else if (A[a][i] == 'P' && A[b][i] == 'G')
            {
                won[j].first++;
            }
            else if (A[a][i] == A[b][i])
            {
                continue;
            }
            else
            {
                won[j + 1].first++;
            }
        }
        sort(won);
        reverse(won);
    }
    for (int i = 0; i < won.size(); i++)
    {
        cout << -won[i].second + 1 << endl;
    }
}