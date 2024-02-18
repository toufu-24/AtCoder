#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> W_sum(N + 1, 0), E_sum(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        W_sum[i + 1] = W_sum[i] + (S[i] == 'W');
    }
    for (int i = N - 1; i >= 0; i--)
    {
        E_sum[i] = E_sum[i + 1] + (S[i] == 'E');
    }

    int ans = 1e9;
    for (int i = 0; i <= N; i++)
    {
        ans = min(ans, W_sum[i] + E_sum[i + 1]);
    }
    cout << ans;
}