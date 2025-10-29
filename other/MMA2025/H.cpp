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

// https://algo-method.com/descriptions/119#h2-61
vector<pair<long long, long long>> prime_factorize(long long N) {
    // 答えを表す可変長配列
    vector<pair<long long, long long>> res;

    // √N まで試し割っていく
    for (long long p = 2; p * p <= N; ++p) {
        // N が p で割り切れないならばスキップ
        if (N % p != 0) {
            continue;
        }

        // N の素因数 p に対する指数を求める
        int e = 0;
        while (N % p == 0) {
            // 指数を 1 増やす
            ++e;

            // N を p で割る
            N /= p;
        }

        // 答えに追加
        res.emplace_back(p, e);
    }

    // 素数が最後に残ることがありうる
    if (N != 1) {
        res.emplace_back(N, 1);
    }
    return res;
}

// https://algo-method.com/descriptions/84#h2-44
// N の約数をすべて求める関数
vector<long long> calc_divisors(long long N) {
    // 答えを表す集合
    vector<long long> res;

    // 各整数 i が N の約数かどうかを調べる
    for (long long i = 1; i * i <= N; ++i) {
        // i が N の約数でない場合はスキップ
        if (N % i != 0) continue;

        // i は約数である
        res.push_back(i);

        // N ÷ i も約数である (重複に注意)
        if (N / i != i) res.push_back(N / i);
    }

    // 約数を小さい順に並び替えて出力
    sort(res.begin(), res.end());
    return res;
}

int pow2(int n) {
    return n * n;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int L;
        cin >> L;
        if (L % 2 == 0) {
            int tmp = L / 2;
            auto factors = prime_factorize(tmp);
            int m = factors[0].first * factors[0].second;
            int n = tmp / m;
            if (m * m - n * n < 0) {
                swap(m, n);
            }
            cout << m * m - n * n << " " << 2 * m * n << " " << m * m + n * n << endl;
            assert(pow2(m * m - n * n) + pow2(2 * m * n) == pow2(m * m + n * n));
        } else {
            bool printed = false;
            auto divs = calc_divisors(L);
            for (int i = 0; i < divs.size(); i++) {
                int p = divs[i];
                int q = L / p;
                int gc = gcd(p, q);
                p /= gc;
                q /= gc;
                if (p * p - q * q < 0) {
                    swap(p, q);
                }
                if ((pow2(p) + pow2(q)) % 2 == 0 && (pow2(p) - pow2(q)) % 2 == 0) {
                    cout << (p * p - q * q) / 2 * gc << " " << p * q * gc << " " << (p * p + q * q) / 2 * gc << endl;
                    assert(pow2((p * p - q * q) / 2 * gc) + pow2(p * q * gc) == pow2((p * p + q * q) / 2 * gc));
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                assert(false);
            }
        }
    }
}