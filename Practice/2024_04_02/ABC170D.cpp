#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

// https://algo-method.com/descriptions/84 より
// N の約数をすべて求める関数
vector<long long> calc_divisors(long long N)
{
    // 答えを表す集合
    vector<long long> res;

    // 各整数 i が N の約数かどうかを調べる
    for (long long i = 1; i * i <= N; ++i)
    {
        // i が N の約数でない場合はスキップ
        if (N % i != 0)
            continue;

        // i は約数である
        res.push_back(i);

        // N ÷ i も約数である (重複に注意)
        if (N / i != i)
            res.push_back(N / i);
    }

    // 約数を小さい順に並び替えて出力
    sort(res.begin(), res.end());
    return res;
}

int32_t main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    unordered_map<int, int> cnt;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        cnt[A[i]]++;
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        auto div = calc_divisors(A[i]);
        for (int j = 0; j < div.size(); j++)
        {
            int d = div[j];
            if (cnt.contains(d) && d != A[i])
            {
                ans++;
                break;
            }
            else if (cnt.contains(d))
            {
                if (cnt[d] > 1)
                {
                    ans++;
                    break;
                }
            }
        }
    }
    cout << N - ans << endl;
}
