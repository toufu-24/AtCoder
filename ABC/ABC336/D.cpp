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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> left(N);
    vector<int> right(N);
    int base = 1;
    for (int i = 0; i < N; i++)
    {
        if (A[i] >= base)
        {
            left[i] = base;
        }
        else
        {
            base = (i == 0 ? 1 : min(left[i - 1], A[i]));
            left[i] = base;
        }
        base++;
    }
    base = 1;
    for (int i = N - 1; i >= 0; i--)
    {
        if (A[i] >= base)
        {
            right[i] = base;
        }
        else
        {
            base = (i == N - 1 ? 1 : min(right[i + 1], A[i]));
            right[i] = base;
        }
        base++;
    }

    int ans = 1;
    for (int i = 0; i < N; i++)
    {
        ans = max(ans, min({left[i], right[i]}));
    }
    cout << ans << endl;
}