#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

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

int main()
{
    vector<bool> is_prime = Eratosthenes(300);
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    for (int i = A; i <= B; i++)
    {
        bool enable = false;
        for (int j = C; j <= D; j++)
        {
            if (is_prime[i + j])
            {
                enable = true;
                break;
            }
        }
        if (!enable)
        {
            cout << "Takahashi";
            return 0;
        }
    }
    cout << "Aoki";
}