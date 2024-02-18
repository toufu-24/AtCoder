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

vector<int> fac(int N)
{
    vector<int> res;
    for (int i = 2; i * i <= N; i++)
    {
        while (N % i == 0)
        {
            res.push_back(i);
            N /= i;
        }
    }
    if (N != 1)
        res.push_back(N);
    return res;
}

int32_t main()
{
    int N;
    cin >> N;
    vector<int> prime_factors = fac(N);
    int ans = numeric_limits<int>::max();
    for (int i = 0; i < (1 << prime_factors.size()); i++)
    {
        int a = 1, b = 1;
        for (int j = 0; j < prime_factors.size(); j++)
        {
            if (i & (1 << j))
                a *= prime_factors[j];
            else
                b *= prime_factors[j];
        }
        assert(a * b == N);
        ans = min(ans, a - 1 + b - 1);
    }
    cout << ans << endl;
}