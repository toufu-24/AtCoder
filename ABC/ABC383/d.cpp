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

// 1 以上 N 以下の整数が素数かどうかを返す
vector<bool> Eratosthenes(int N) {
    // テーブル
    vector<bool> isprime(N + 1, true);

    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p) {
        // すでに合成数であるものはスキップする
        if (!isprime[p])
            continue;

        // p 以外の p の倍数から素数ラベルを剥奪
        for (int q = p * 2; q <= N; q += p) {
            isprime[q] = false;
        }
    }

    // 1 以上 N 以下の整数が素数かどうか
    return isprime;
}

int32_t main() {
    int n;
    cin >> n;
    int ans = 0;
    // 約数の個数が9個の数は、素因数分解すると
    // p1^2, p2^2 -> 1, p1, p2, p1*p2, p1^2, p2^2, p1*p2^2, p1^2*p2, p1^2*p2^2
    // p1^8 -> 1, p1, p1^2, p1^3, p1^4, p1^5, p1^6, p1^7, p1^8
    vector<bool> isprime = Eratosthenes(1e7);
    // p1^2, p2^2
    for (int i = 1; i * i <= n; i++) {
        if (isprime[i]) {
            for (int j = 1; j <= n; j++) {
                if (i <= j) {
                    break;
                }
                if (i * i * j * j <= n) {
                    if (isprime[j]) {
                        ans++;
                    }
                } else {
                    break;
                }
            }
        }
    }
    // p1^8
    for (int i = 1; i <= n; i++) {
        if (isprime[i]) {
            if (i * i * i * i * i * i * i * i <= n) {
                ans++;
            } else {
                break;
            }
        }
    }
    cout << ans << endl;
}
