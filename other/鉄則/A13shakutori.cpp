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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);

    vector<int> R(N);
    for (int i = 0; i < N; i++)
    {
        R[i] = R[i - 1];
        while (R[i] < N && A[R[i]] - A[i] <= K)
        {
            R[i]++;
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans += R[i] - i - 1;
    }
    cout << ans << endl;
}