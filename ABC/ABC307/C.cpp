#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

// vector<vector<char>> removeDots(const vector<vector<char>> &matrix)
// {
//     vector<vector<char>> result;
//     for (const auto &row : matrix)
//     {
//         vector<char> new_row;
//         for (const auto &ch : row)
//         {
//             if (ch != '.')
//             {
//                 new_row.push_back(ch);
//             }
//         }
//         if (new_row.size() > 0)
//             result.push_back(new_row);
//     }
//     return result;
// }

int main()
{
    int H_A, W_A;
    cin >> H_A >> W_A;
    vector<vector<char>> A(H_A, vector<char>(W_A));
    for (int i = 0; i < H_A; i++)
    {
        for (int j = 0; j < W_A; j++)
        {
            cin >> A[i][j];
        }
    }
    // A = removeDots(A);
    // H_A = A.size();
    // W_A = A[0].size();
    int H_B, W_B;
    cin >> H_B >> W_B;
    vector<vector<char>> B(H_B, vector<char>(W_B));
    for (int i = 0; i < H_B; i++)
    {
        for (int j = 0; j < W_B; j++)
        {
            cin >> B[i][j];
        }
    }
    // B = removeDots(B);
    // H_B = B.size();
    // W_B = B[0].size();
    int H_X, W_X;
    cin >> H_X >> W_X;
    vector<vector<char>> X(H_X, vector<char>(W_X));
    for (int i = 0; i < H_X; i++)
    {
        for (int j = 0; j < W_X; j++)
        {
            cin >> X[i][j];
        }
    }

    for (int i = 0; i < H_X; i++)
    {
        for (int j = 0; j < W_X; j++)
        {
            vector<vector<char>> C(H_X, vector<char>(W_X, '.'));
            bool ans = true;
            for (int k = 0; k < H_X; k++)
            {
                for (int l = 0; l < W_X; l++)
                {
                    for (int x = 0; x < H_A; x++)
                    {
                        for (int y = 0; y < W_A; y++)
                        {
                            if (A[x][y] == '#')
                            {
                                if (i * H_A + x < H_X)
                                {
                                    continue;
                                }
                                if (j * W_A + y < W_X)
                                {
                                    continue;
                                }
                                C[i * H_A + x][j * W_A + y] = A[x][y];
                            }
                        }
                    }
                    ans = true;
                    for (int x = 0; x < H_B; x++)
                    {
                        for (int y = 0; y < W_B; y++)
                        {
                            if (B[x][y] == '#')
                            {
                                if (k * H_B + x < H_X)
                                {
                                    continue;
                                }
                                if (l * W_B + y < W_X)
                                {
                                    continue;
                                }
                                C[k * H_B + x][l * W_B + y] = B[x][y];
                            }
                        }
                    }
                    for (int x = 0; x < H_X; x++)
                    {
                        for (int y = 0; y < W_X; y++)
                        {
                            if (C[x][y] != X[x][y])
                            {
                                ans = false;
                            }
                        }
                    }
                    if (ans)
                    {
                        cout << "Yes" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "No" << endl;
}
