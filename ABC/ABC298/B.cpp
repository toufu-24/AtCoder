#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
        }
    }
    vector<vector<int>> B(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> B[i][j];
        }
    }
    // AとBが一致するか判定
    bool ans = false;
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((A[i][j] == 1) && B[i][j] != 1)
            {
                flag = false;
                break;
            }
        }
    }
    if (flag)
    {
        ans = true;
    }

    vector<vector<int>> A2(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A2[N - j - 1][i] = A[i][j];
        }
    }
    // A2とBが一致するか判定
    bool flag4 = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((A2[i][j] == 1) && B[i][j] != 1)
            {
                flag4 = false;
                break;
            }
        }
    }
    if (flag4)
    {
        ans = true;
    }

    vector<vector<int>> A3(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A3[N - j - 1][i] = A2[i][j];
        }
    }
    // A3とBが一致するか判定
    bool flag2 = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((A3[i][j] == 1) && B[i][j] != 1)
            {
                flag2 = false;
                break;
            }
        }
    }
    if (flag2)
    {
        ans = true;
    }

    vector<vector<int>> A4(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A4[N - j - 1][i] = A3[i][j];
        }
    }
    // A4とBが一致するか判定
    bool flag3 = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((A4[i][j] == 1) && B[i][j] != 1)
            {
                flag3 = false;
                break;
            }
        }
    }
    if (flag3)
    {
        ans = true;
    }

    if (ans)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}