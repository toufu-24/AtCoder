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
    int N, D;
    cin >> N >> D;

    vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }
    vector<int> dp(N, 1);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (abs(A[i] - A[j]) <= D)
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(all(dp)) << endl;
}