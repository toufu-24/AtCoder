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
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        string S;
        cin >> S;
        for (int j = 0; j < N; j++)
        {
            A[i][j] = S[j] - '0';
        }
    }
    // マス目の外側のマスに書かれた整数を時計回りに 1 個ずつずらす
    vector<int> side;
    for (int i = 0; i < N; i++)
    {
        side.push_back(A[0][i]);
    }
    for (int i = 1; i < N; i++)
    {
        side.push_back(A[i][N - 1]);
    }
    for (int i = N - 2; i >= 0; i--)
    {
        side.push_back(A[N - 1][i]);
    }
    for (int i = N - 2; i > 0; i--)
    {
        side.push_back(A[i][0]);
    }

    int cnt = 0;
    for (int i = 1; i < N; i++)
    {
        A[0][i] = side[cnt++];
    }
    for (int i = 1; i < N; i++)
    {
        A[i][N - 1] = side[cnt++];
    }
    for (int i = N - 2; i >= 0; i--)
    {
        A[N - 1][i] = side[cnt++];
    }
    for (int i = N - 2; i >= 0; i--)
    {
        A[i][0] = side[cnt++];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << A[i][j] ;
        }
        cout << endl;
    }
}