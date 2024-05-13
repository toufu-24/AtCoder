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
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int ans = 0;
    int now = 0;
    for (int i = 0; i < N; i++)
    {
        if (now + A[i] <= K)
        {
            now += A[i];
        }
        else
        {
            now = 0;
            ans++;
            i--;
        }
    }
    if (now > 0)
    {
        ans++;
    }
    cout << ans << endl;
}
