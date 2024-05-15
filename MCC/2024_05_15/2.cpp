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
    vector<int> A_cnt(1e6, 0);
    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A_cnt[A[i]]++;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += A_cnt[B[C[i] - 1]];
    }
    cout << ans << endl;
}
