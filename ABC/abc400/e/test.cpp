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

// https://qiita.com/drken/items/a14e9af0ca2d857dad23#4-%E7%B4%A0%E5%9B%A0%E6%95%B0%E5%88%86%E8%A7%A3
vector<pair<long long, long long>> prime_factorize(long long N) {
    vector<pair<long long, long long>> res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0)
            continue;
        long long ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1)
        res.push_back({N, 1});
    return res;
}

int32_t main() {
    for (int i = 0; i < 1000; i++) {
        auto p = prime_factorize(i);
        if (p.size() == 2) {
            bool ok = true;
            for (auto x : p) {
                if (x.second % 2 != 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                cout << i << endl;
            }
        }
    }
}
