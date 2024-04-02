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

// https://algo-method.com/descriptions/84　より
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
    int ans = 0;
    for (int i = 1; i <= N; i += 2)
    {
        auto div = calc_divisors(i);
        if (div.size() == 8)
        {
            ans++;
        }
    }
    cout << ans << endl;
}
