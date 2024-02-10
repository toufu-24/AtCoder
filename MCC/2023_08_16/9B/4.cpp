#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

using mint = modint1000000007;

vector<int> prime_factorization(int n)
{
    vector<int> res;
    for (int i = 2; i * i <= n; i++)
    {
        int cnt = 0;
        while (n % i == 0)
        {
            cnt++;
            n /= i;
        }
        if (cnt > 0)
        {
            res.push_back(i);
        }
    }
    return res;
}

int main()
{
    int N;
    cin >> N;
    mint ans = 1;
    for (int i = 1; i <= N; i++)
    {
        vector<int> pf = prime_factorization(i);
        mint tmp = 0;
        for (int j = 0; j < pf.size(); j++)
        {
            tmp += pf[j];
        }
        ans += tmp;
    }
    cout << ans.val() << endl;
}