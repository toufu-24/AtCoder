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

#define int ll

int N, M;
int32_t main()
{
    cin >> N >> M;
    modint::set_mod(M);
    vector<modint> A(N);
    ll sum = 0;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        A[i] = tmp;
        sum += tmp;
    }
    sort(
        all(A), [](modint a, modint b)
        { return a.val() % M < b.val() % M; });
    int ans = 1e18;
    for (int i = 0; i < N; i++)
    {
        ll tmp = sum - A[i].val();
        int j;
        for (j = i + 1; j != i && (A[i] != A[i + 1] || A[i] != A[i + 1] + 1); j++, j %= N)
        {
            tmp -= A[j].val();
            ans = min(ans, tmp);
        }
        if (i >= j)
        {
            break;
        }
        i = j - 1;
    }
    cout << ans << endl;
}