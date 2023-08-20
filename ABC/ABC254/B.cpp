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
    vector<vector<int>> A(N + 1);
    for (int i = 1; i <= N; i++)
    {
        A[i].resize(i, 1);
        for (int j = 0; j < i; j++)
        {
            if (j == 0 || j + 1 == i)
                A[i][j] = 1;
            else
                A[i][j] = A[i - 1][j - 1] + A[i - 1][j];
        }
        for (int j = 0; j < i; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}