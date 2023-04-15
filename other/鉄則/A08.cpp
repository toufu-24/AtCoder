#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<int>> X(H + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> X[i][j];
        }
    }
    // 累積和
    // 横方向
    for (int i = 1; i <= H; i++)
    {
        for (int j = 2; j <= W; j++)
        {
            X[i][j] += X[i][j - 1];
        }
    }
    // 縦方向
    for (int i = 1; i <= W; i++)
    {
        for (int j = 2; j <= H; j++)
        {
            X[j][i] += X[j - 1][i];
        }
    }

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        cout << X[C][D] - X[C][B - 1] - X[A - 1][D] + X[A - 1][B - 1] << endl;
    }
}