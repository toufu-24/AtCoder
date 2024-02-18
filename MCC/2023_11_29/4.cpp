#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

// 1 以上 N 以下の整数が素数かどうかを返す
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
    vector<int> prime;
    auto v = Eratosthenes(1e7);
    for (int i = 2; i <= v.size(); i++)
    {
        if (v[i])
        {
            prime.push_back(i);
        }
    }

    vector<int> ans(N, 1);
    for (int i = 0; i < N; i++)
    {
        int next_prime = prime[i];
        for (int j = 0; j < N - 1; j++)
        {
            int idx = (i + j) % N;
            ans[idx] *= next_prime;
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << " ";
    }
}