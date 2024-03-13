#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int V1, V2, V3;
    cin >> V1 >> V2 >> V3;
    vector<vector<vector<int>>> v(15, vector<vector<int>>(15, vector<int>(15, 0)));
    int a1 = 0, b1 = 0, c1 = 0; // 1は原点で固定
    for (int a2 = 0; a2 <= 7; a2++)
    {
        for (int b2 = 0; b2 <= 7; b2++)
        {
            for (int c2 = 0; c2 <= 7; c2++)
            {
                for (int a3 = 0; a3 <= 7; a3++)
                {
                    for (int b3 = 0; b3 <= 7; b3++)
                    {
                        for (int c3 = 0; c3 <= 7; c3++)
                        {
                            v = vector<vector<vector<int>>>(15, vector<vector<int>>(15, vector<int>(15, 0)));
                            for (int i = 0; i < 7; i++)
                            {
                                for (int j = 0; j < 7; j++)
                                {
                                    for (int k = 0; k < 7; k++)
                                    {
                                        v[a1 + i][b1 + j][c1 + k]++;
                                        v[a2 + i][b2 + j][c2 + k]++;
                                        v[a3 + i][b3 + j][c3 + k]++;
                                    }
                                }
                            }

                            int one = 0, two = 0, three = 0;
                            for (int i = 0; i < 15; i++)
                            {
                                for (int j = 0; j < 15; j++)
                                {
                                    for (int k = 0; k < 15; k++)
                                    {
                                        if (v[i][j][k] == 1)
                                        {
                                            one++;
                                            if (one > V1)
                                                goto b;
                                        }
                                        else if (v[i][j][k] == 2)
                                        {
                                            two++;
                                            if (two > V2)
                                                goto b;
                                        }
                                        else if (v[i][j][k] == 3)
                                        {
                                            three++;
                                            if (three > V3)
                                                goto b;
                                        }
                                    }
                                }
                            }
                            if (one == V1 && two == V2 && three == V3)
                            {
                                cout << "Yes" << endl;
                                cout << a1 << " " << b1 << " " << c1 << " ";
                                cout << a2 << " " << b2 << " " << c2 << " ";
                                cout << a3 << " " << b3 << " " << c3 << endl;
                                return 0;
                            }
                        b:;
                        }
                    }
                }
            }
        }
    }
    cout << "No" << endl;
}