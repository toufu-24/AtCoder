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
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
        }
    }
    int ans = 0;
    int maxSum = 0;
    vector<vector<int>> prefixSum(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + A[i - 1][j - 1];
        }
    }
    int max_i = 0, max_j = 0;
    for (int i = M; i <= N; i++)
    {
        for (int j = M; j <= N; j++)
        {
            int sum = prefixSum[i][j] - prefixSum[i - M][j] - prefixSum[i][j - M] + prefixSum[i - M][j - M];
            maxSum = max(maxSum, sum);
            if (maxSum == sum)
            {
                max_i = i;
                max_j = j;
            }
        }
    }
    int secondMaxSum = 0;
    int secondMax_i = 0, secondMax_j = 0;
    for (int i = M; i <= N; i++)
    {
        for (int j = M; j <= N; j++)
        {
            int sum = prefixSum[i][j] - prefixSum[i - M][j] - prefixSum[i][j - M] + prefixSum[i - M][j - M];
            if (i >= max_i && i < max_i + M && j >= max_j && j < max_j + M)
            {
                sum = 0;
            }
            if (i - M <= max_i && i - M >= max_i + M && j - M <= max_j && j - M >= max_j + M)
            {
                sum = 0;
            }
            if (i <= max_i && i >= max_i + M && j - M <= max_j && j - M >= max_j + M)
            {
                sum = 0;
            }
            if (i - M <= max_i && i - M >= max_i + M && j <= max_j && j >= max_j + M)
            {
                sum = 0;
            }
            secondMaxSum = max(secondMaxSum, sum);
            if (secondMaxSum == sum)
            {
                secondMax_i = i;
                secondMax_j = j;
            }
        }
    }
    int thirdMaxSum = 0;
    int thirdMax_i = 0, thirdMax_j = 0;
    for (int i = M; i <= N; i++)
    {
        for (int j = M; j <= N; j++)
        {
            int sum = prefixSum[i][j] - prefixSum[i - M][j] - prefixSum[i][j - M] + prefixSum[i - M][j - M];
            if (i >= max_i && i < max_i + M && j >= max_j && j < max_j + M)
            {
                sum = 0;
            }
            if (i - M <= max_i && i - M >= max_i + M && j - M <= max_j && j - M >= max_j + M)
            {
                sum = 0;
            }
            if (i <= max_i && i >= max_i + M && j - M <= max_j && j - M >= max_j + M)
            {
                sum = 0;
            }
            if (i - M <= max_i && i - M >= max_i + M && j <= max_j && j >= max_j + M)
            {
                sum = 0;
            }
            if (i >= secondMax_i && i < secondMax_i + M && j >= secondMax_j && j < secondMax_j + M)
            {
                sum = 0;
            }
            if (i - M <= secondMax_i && i - M >= secondMax_i + M && j - M <= secondMax_j && j - M >= secondMax_j + M)
            {
                sum = 0;
            }
            if (i <= secondMax_i && i >= secondMax_i + M && j - M <= secondMax_j && j - M >= secondMax_j + M)
            {
                sum = 0;
            }
            if (i - M <= secondMax_i && i - M >= secondMax_i + M && j <= secondMax_j && j >= secondMax_j + M)
            {
                sum = 0;
            }
            thirdMaxSum = max(thirdMaxSum, sum);
            if (thirdMaxSum == sum)
            {
                thirdMax_i = i;
                thirdMax_j = j;
            }
        }
    }
    ans = maxSum + secondMaxSum + thirdMaxSum;
    cout << ans << endl;
}
