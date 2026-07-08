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

vector<pair<long long, long long>> prime_factorize(long long N) {
    vector<pair<long long, long long>> res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
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
    if (N != 1) res.push_back({N, 1});
    return res;
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<set<int>> primes(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        auto ret = prime_factorize(a[i]);
        for (auto [pri, cnt] : ret) {
            primes[i].insert(pri);
        }
    }
    // 2か1
    for (auto x : primes[0]) {
        bool ok = true;
        for (int i = 0; i < n; i++) {
            ok &= primes[i].contains(x);
        }
        if (ok) {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 2 << endl;
}
