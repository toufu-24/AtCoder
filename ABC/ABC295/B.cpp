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
    int R, C;
    cin >> R >> C;
    vector<string> B(R);
    for (int i = 0; i < R; i++)
    {
        cin >> B[i];
    }

    for (int i = 1; i <= 9; i++)
    {
        for (int j = 0; j < R; j++)
        {
            for (int k = 0; k < C; k++)
            {
                if (int(B[j][k] - '0') == i)
                {
                    for (int l = j - i; l <= j + i; l++)
                    {
                        if (l >= 0 && l < R)
                        {
                            for (int m = k; (m - k) + abs(l - j) <= i; m++)
                            {
                                if (m >= 0 && m < C)
                                    if (!(B[l][m] >= '0' && B[l][m] <= '9'))
                                        B[l][m] = '.';
                            }
                            for (int m = k; abs(m - k) + abs(l - j) <= i; m--)
                            {
                                if (m >= 0 && m < C)
                                    if (!(B[l][m] >= '0' && B[l][m] <= '9'))
                                        B[l][m] = '.';
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < R; i++)
    {
        for (int k = 0; k < C; k++)
        {
            if ((B[i][k] >= '0' && B[i][k] <= '9'))
            {
                B[i][k] = '.';
            }
        }
        cout << B[i] << "\n";
    }
}