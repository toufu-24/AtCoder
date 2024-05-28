#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N, T;
    cin >> N >> T;
    vector<vector<int>> bingo(N, vector<int>(N));
    map<int, pair<int, int>> pos;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            bingo[i][j] = i * N + j + 1;
            pos[bingo[i][j]] = {i, j};
        }
    }

    vector<int> A(T);
    for (int i = 0; i < T; i++)
    {
        cin >> A[i];
    }

    vector<int> row_count(N, 0), col_count(N, 0);
    int naname1 = 0, naname2 = 0;

    for (int t = 0; t < T; t++)
    {
        int num = A[t];
        int x = pos[num].first;
        int y = pos[num].second;
        row_count[x]++;
        col_count[y]++;
        if (x == y)
            naname1++;
        if (x + y == N - 1)
            naname2++;

        if (row_count[x] == N || col_count[y] == N || naname1 == N || naname2 == N)
        {
            cout << t + 1 << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}
