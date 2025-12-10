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

// https://algo-method.com/descriptions/64#h2-52
//  1 以上 N 以下の整数が素数かどうかを返す
vector<bool> Eratosthenes(int N) {
    // テーブル
    vector<bool> isprime(N + 1, true);

    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p) {
        // すでに合成数であるものはスキップする
        if (!isprime[p]) continue;

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
    auto era = Eratosthenes(1e6 + 10);
    vector<int> primes;
    for (int i = 0; i < 1e6 + 10; i++) {
        if (era[i]) {
            primes.push_back(i);
        }
    }

    int ans = 0;
    for (int i = 1; i < primes.size(); i++) {
        int b = primes[i];
        if (b > n) {
            break;
        }
        for (int j = i + 1; j < primes.size(); j++) {
            int c = primes[j];
            if (b * c * c > n) {
                break;
            }
            ld tmp = (ld)(n) / (b * c * c);
            tmp = sqrtl(tmp) + 10;
            int idx = min(lower_bound(all(primes), tmp) - primes.begin(), i - 1);
            while (primes[idx] * primes[idx] * b * c * c > n) {
                idx--;
                if (idx == -1) {
                    break;
                }
            }
            if (idx == -1) {
                continue;
            }
            // if (primes[idx] * primes[idx] * b * c * c < 0) {
            //     cout << "overflow" << endl;
            //     return 1;
            // }
            // cerr << primes[idx] << " " << b << " " << c << endl;
            ans += idx + 1;
        }
    }
    cout << ans << endl;
}
