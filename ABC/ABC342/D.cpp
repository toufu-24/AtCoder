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
    SORT(A);
    vector<set<int>> prime_factors(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 2; j * j <= A[i]; j++)
        {
            while (A[i] % j == 0)
            {
                if (prime_factors[i].count(j))
                {
                    prime_factors[i].erase(j);
                }
                else
                {
                    prime_factors[i].insert(j);
                }
                A[i] /= j;
            }
        }
        if (A[i] > 1)
        {
            prime_factors[i].insert(A[i]);
        }
    }
    vector<int> mul;
    for (int i = 0; i < N; i++)
    {
        int seki = 1;
        for (int prime : prime_factors[i])
        {
            seki *= prime;
        }
        if (A[i] == 0)
        {
            seki = 0;
        }
        mul.push_back(seki);
    }
    SORT(mul);

    int ans = 0;
    map<int, int> cnt;
    for (int i = 0; i < N; i++)
    {
        if (mul[i] == 0)
        {
            ans += N - i - 1;
            continue;
        }
        int now = mul[i];
        int lower = lower_bound(all(mul), now) - mul.begin();
        int upper = upper_bound(all(mul), now) - mul.begin();
        cnt[now]++;
        int diff = upper - lower;
        ans += diff - cnt[now];
    }
    cout << ans << endl;
}