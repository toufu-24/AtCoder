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

// https://qiita.com/drken/items/a14e9af0ca2d857dad23#3-%E7%B4%84%E6%95%B0%E5%88%97%E6%8C%99  より
vector<int> enum_divisors(const int N)
{
    vector<int> res;
    for (int i = 1; i * i <= N; ++i)
    {
        if (N % i == 0)
        {
            res.push_back(i);
            // 重複しないならば i の相方である N/i も push
            if (N / i != i)
                res.push_back(N / i);
        }
    }
    // 小さい順に並び替える
    sort(res.begin(), res.end());
    return res;
}

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
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        vector<int> divs = enum_divisors(A[i]);
        for (const auto &div : divs)
        {
            if (!binary_search(all(A), div))
            {
                continue;
            }
            assert(A[i] % div == 0);
            int tmp = A[i] / div;
            int low = lower_bound(all(A), tmp) - A.begin();
            int up = upper_bound(all(A), tmp) - A.begin();
            int div_low = lower_bound(all(A), div) - A.begin();
            int div_up = upper_bound(all(A), div) - A.begin();
            int div_num = div_up - div_low;
            ans += div_num * (up - low);
        }
    }
    cout << ans << endl;
}
