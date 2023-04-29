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
    vector<vector<char>> A(H, vector<char>(W));
    vector<vector<char>> B(H, vector<char>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> B[i][j];
        }
    }

    // 縦シフト、横シフトして一致するか判定
    for (int i = 0; i <= H; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            // Bを左シフト
            vector<char> tmp;
            for (int k = 0; k < H; k++)
            {
                tmp.push_back(B[k][0]);
            }
            for (int k = 0; k < H; k++)
            {
                for (int l = 0; l < W - 1; l++)
                {
                    B[k][l] = B[k][l + 1];
                }
            }
            for (int k = 0; k < H; k++)
            {
                B[k][W - 1] = tmp[k];
            }

            // 一致するか判定
            bool flag = true;
            for (int k = 0; k < H; k++)
            {
                for (int l = 0; l < W; l++)
                {
                    if (A[k][l] != B[k][l])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag)
            {
                cout << "Yes" << endl;
                return 0;
            }
        }
        // Bを上シフト
        vector<char> tmp;
        for (int k = 0; k < W; k++)
        {
            tmp.push_back(B[0][k]);
        }
        for (int k = 0; k < H - 1; k++)
        {
            for (int l = 0; l < W; l++)
            {
                B[k][l] = B[k + 1][l];
            }
        }
        for (int k = 0; k < W; k++)
        {
            B[H - 1][k] = tmp[k];
        }
    }
    cout << "No" << endl;
}