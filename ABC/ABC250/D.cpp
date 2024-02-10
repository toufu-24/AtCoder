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
#include <iostream>
#include <vector>
using namespace std;

// https://algo-method.com/descriptions/64より
//  1 以上 N 以下の整数が素数かどうかを返す
vector<bool> Eratosthenes(int N)
{
    // テーブル
    vector<bool> isprime(N + 1, true);

    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p)
    {
        // すでに合成数であるものはスキップする
        if (!isprime[p])
            continue;

        // p 以外の p の倍数から素数ラベルを剥奪
        for (int q = p * 2; q <= N; q += p)
        {
            isprime[q] = false;
        }
    }

    // 1 以上 N 以下の整数が素数かどうか
    return isprime;
}

int32_t main()
{
    int N;
    cin >> N;
    auto isprime = Eratosthenes(1e6 + 10);
    vector<int> prime;
    int ans = 0;
    for (int i = 0; i < 1e6 + 10; i++)
    {
        if (!isprime[i])
        {
            continue;
        }
        int tmp = i * i * i;
        if (tmp > N)
        {
            break;
        }
        // Nを超えない最大の素数を探す
        int idx = upper_bound(all(prime), N / tmp) - prime.begin();
        ans += idx;
        prime.push_back(i);
    }

    cout << ans << endl;
}