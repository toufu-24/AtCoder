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
    vector<vector<int>> A(N, vector<int>(2));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[j][i];
        }
    }
    // 累積和
    vector<vector<int>> sum(N, vector<int>(2));
    sum[0][0] = A[0][0];
    for (int i = 1; i < N; i++)
    {
        sum[i][0] = sum[i - 1][0] + A[i][0];
    }
    sum[N - 1][1] = A[N - 1][1];
    for (int i = N - 2; i >= 0; i--)
    {
        sum[i][1] = sum[i + 1][1] + A[i][1];
    }

    // i列目で降りた時の最大値
    int maximum = 0;
    for (int i = 0; i < N; i++)
    {
        int tmp = sum[i][0] + sum[i][1];
        maximum = max(maximum, tmp);
    }

    cout << maximum;
}