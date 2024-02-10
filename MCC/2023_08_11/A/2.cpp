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
    int H, W;
    cin >> H >> W;
    vector<vector<char>> A(H + 2, vector<char>(W + 2, '#'));
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < H + 2; i++)
    {
        for (int j = 0; j < W + 2; j++)
        {
            cout << A[i][j];
        }
        cout << endl;
    }
}