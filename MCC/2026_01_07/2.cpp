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
// 素因数分解
// 460 = 2^2 x 5 x 23 の場合
// 返り値は {{2, 2}, {5, 1}, {23, 1}}
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

int32_t main() {
    int x;
    cin >> x;
    if (x <= 3) {
        cout << 1 << endl;
        return 0;
    }
    int ans = 0;
    for (int i = 2; i <= x; i++) {
        auto ret = prime_factorize(i);
        int tmp = ret[0].second;
        bool ok = true;
        for (auto x : ret) {
            if (tmp != x.second) {
                ok = false;
            }
        }
        if(tmp == 1){
            ok = false;
        }
        if(ok){
            ans = i;
        }
    }
    cout << ans << endl;
}