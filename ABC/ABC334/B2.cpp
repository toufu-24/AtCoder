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

int correct(int A, int M, int L, int R)
{
    int ans = 0;
    for (int i = L; i <= R; i++)
    {
        if ((i - A) % M == 0)
        {
            ans++;
        }
    }
    return ans;
}

int solve(int A, int M, int L, int R)
{
    L -= A;
    R -= A;
    ll ans = R / M - L / M;
    if (R >= 0 && L < 0)
    {
        ans++;
    }
    return ans;
}

int32_t main()
{
    int A, M, L, R;
    for (int i = 0; i < 1e3; i++)
    {
        A = rand() % 100;
        M = rand() % 100 + 1;
        L = rand() % 100;
        R = rand() % 100;
        if (L > R)
            swap(L, R);
        if (correct(A, M, L, R) != solve(A, M, L, R))
        {
            cout << A << " " << M << " " << L << " " << R << endl;
            cout << correct(A, M, L, R) << " " << solve(A, M, L, R) << endl;
            return 0;
        }
    }
    cerr << "OK" << endl;
    cin >> A >> M >> L >> R;
    cout << solve(A, M, L, R) << endl;
}