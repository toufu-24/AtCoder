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
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> B[i];
    }
    vector<int> sum_A(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        sum_A[i + 1] = sum_A[i] + A[i];
    }
    vector<int> sum_B(M + 1, 0);
    for (int i = 0; i < M; i++)
    {
        sum_B[i + 1] = sum_B[i] + B[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        if (sum_A[i + 1] > K)
        {
            break;
        }
        int idx = upper_bound(all(sum_B), K - sum_A[i + 1]) - sum_B.begin();
        idx--;
        // if (sum_B[idx + 1] > K)
        // {
        //     continue;
        // }
        // if (sum_A[i + 1] + sum_B[idx + 1] > K)
        // {
        //     continue;
        // }
        ans = max(ans, i + idx + 1);
    }
    int B_idx = upper_bound(all(sum_B), K) - sum_B.begin();
    B_idx--;
    ans = max(ans, B_idx);
    cout << ans << endl;
}