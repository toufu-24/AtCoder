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

#define int ll

int32_t main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> B(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> B[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (B[i][j] < 1)
            {
                cout << "No" << endl;
                return 0;
            }
            if (B[0][i] % 7 > 7)
            {
                cout << "No" << endl;
                return 0;
            }
            if (B[i][0] % 7 < 1)
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i < M; i++)
    {
        if (B[0][i] == B[0][i - 1] + 1)
        {
        }
        else
        {
            cout << "No" << endl;
            return 0;
        }
    }
    for (int i = 1; i < N; i++)
    {
        if (B[i][0] == B[i - 1][0] + 7)
        {
        }
        else
        {
            cout << "No" << endl;
            return 0;
        }
    }

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < M; j++)
        {
            if (B[i][j] == B[i - 1][j] + 7 && B[i][j] == B[i][j - 1] + 1)
            {
            }
            else
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
}
