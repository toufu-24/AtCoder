#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    SORT(A);
    vector<int> S(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        S[i + 1] = S[i] + A[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        int idx = lower_bound(all(A), A[i]) - A.begin();
        ans += S[N] - S[idx] - A[i] * (N - idx);
    }
    cout << ans << endl;
}
