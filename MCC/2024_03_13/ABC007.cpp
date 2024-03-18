#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    string A, B;
    cin >> A >> B;
    vector dpA(A.size() + 1, vector(2, vector(10, 0LL)));
    for (int i = 0; i < A[0] - '0'; i++)
    {
        if (i == 4 || i == 9)
        {
            continue;
        }
        dpA[0][1][i] += 1;
    }
    dpA[0][0][A[0] - '0'] += 1;
    for (int i = 0; i < A.size(); i++)
    {
        for (int flag = 0; flag < 2; flag++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (j == 4 || j == 9)
                {
                    continue;
                }
                for (int k = 0; k < 10; k++)
                {
                    if (k == 4 || k == 9)
                    {
                        continue;
                    }
                    if (!flag && k > A[i] - '0')
                    {
                        continue;
                    }
                    dpA[i + 1][flag || (k != A[i] - '0')][k] += dpA[i][flag][j];
                }
            }
        }
    }
    // -------------------------------------------------------------
    vector dpB(B.size() + 1, vector(2, vector(10, 0LL)));
    for (int i = 0; i < B[0] - '0'; i++)
    {
        dpB[0][1][i] += 1;
    }
    dpB[0][0][B[0] - '0'] += 1;
    for (int i = 0; i < B.size(); i++)
    {
        for (int flag = 0; flag < 2; flag++)
        {
            for (int j = 0; j < 10; j++)
            {
                for (int k = 0; k < 10; k++)
                {
                    if (k == 4 || k == 9)
                    {
                        continue;
                    }
                    if (!flag && k > B[i] - '0')
                    {
                        continue;
                    }
                    dpB[i + 1][flag || (k != B[i] - '0')][k] += dpB[i][flag][j];
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
        ans += (i == 4 || i == 9) ? 0 : ((dpB[B.size()][0][i] + dpB[B.size()][1][i]) - (dpA[A.size()][0][i] + dpA[A.size()][1][i]));
    }
    cout << (stoll(B) - stoll(A) - ans + 1) << endl;
}