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

    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        ll plus = upper_bound(A.begin() + i + 1, A.end(), K + A[i]) - A.begin();
        ans += plus - i - 1;
    }
    cout << ans << endl;
}