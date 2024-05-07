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

// https://qiita.com/drken/items/a14e9af0ca2d857dad23#4-%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3
vector<pair<int, int>> prime_factorize(int N)
{
    vector<pair<int, int>> res;
    for (int a = 2; a * a <= N; ++a)
    {
        if (N % a != 0)
            continue;
        int ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0)
        {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1)
        res.push_back({N, 1});
    return res;
}

int32_t main()
{
    int K;
    cin >> K;
    int ans = K;
    auto primes = prime_factorize(K);
    ans = min(ans, primes.back().first);
    cerr << ans << endl;
    map<int, int> mp;
    for (auto p : primes)
    {
        mp[p.first] = p.second - 1;
        if (mp[p.first] == 0)
        {
            mp.erase(p.first);
        }
    }
    // ans!にpが何個含まれるか
    int ok = K;
    int ng = -1;
    while (ok - ng > 1)
    {
        // mid!に全てのpが含まれるか
        int mid = (ok + ng) / 2;
        // ルジャンドルの定理
        bool include = true;
        for (int i = 0; i < primes.size(); i++)
        {
            int p = primes[i].first;
            int cnt = 0;
            while (true)
            {
                cnt += mid / p;
                if (mid / p == 0)
                {
                    break;
                }
                p *= primes[i].first;
            }
            if (cnt < primes[i].second)
            {
                include = false;
                break;
            }
        }
        if (include)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    cout << ok << endl;
}
