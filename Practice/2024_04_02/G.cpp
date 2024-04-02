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

// https://algo-method.com/descriptions/64 より
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
    // int five = powl(N, (ld)(1) / 3) + 100;
    int five = 2e6;
    auto isprime = Eratosthenes(five);
    vector<int> sum(five + 1, 0);
    for (int i = 0; i < five; i++)
    {
        sum[i + 1] = sum[i] + isprime[i];
    }

    vector<int> prime;
    for (int i = 0; i < five; i++)
    {
        if (isprime[i])
        {
            prime.push_back(i);
        }
    }

    int ans = 0;
    for (int i = 0; i < prime.size(); i++)
    {
        int a = prime[i];
        if (a * a > N)
            break;
        for (int j = i + 1; j < prime.size(); j++)
        {
            int b = prime[j];
            if (a * a * b > N)
                break;
            // b < c <= sqrt(N / a^2b)を満たすcの個数
            int c = sqrtl((ld)(N) / a / a / b);
            if (c <= b)
                break;
            ans += sum[c + 1] - sum[b + 1];
        }
    }

    cout << ans << endl;
}
