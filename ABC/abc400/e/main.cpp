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

// https://algo-method.com/descriptions/64
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
    int Q;
    cin >> Q;
    auto isprime = Eratosthenes(1000000);
    auto primes = vector<int>();
    for (int i = 0; i < isprime.size(); i++) {
        if (isprime[i]) {
            primes.push_back(i);
        }
    }
    // cerr << primes.size() << endl;
    set<int> st;
    for (int i = 0; i < primes.size(); i++) {
        // 1e12 = primes[i]**2 * primes[j]**2 となる最大のj
        int max_idx = lower_bound(all(primes), sqrtl(1e12 / (primes[i] * primes[i]))) - primes.begin();
        for (int j = i + 1; j <= max_idx; j++) {
            // st.insert(primes[i] * primes[i] * primes[j] * primes[j]);
            queue<pair<int, int>> q;
            q.push({2, 2});
            set<pair<int, int>> used;
            used.insert({2, 2});
            while (!q.empty()) {
                auto [i_cnt, j_cnt] = q.front();
                q.pop();
                if (powl(primes[i], i_cnt) * powl(primes[j], j_cnt) > 1e12) {
                    continue;
                }
                st.insert(powl(primes[i], i_cnt) * powl(primes[j], j_cnt));
                if (powl(primes[i], i_cnt + 2) * powl(primes[j], j_cnt) <= 1e12 && !used.contains({i_cnt + 2, j_cnt})) {
                    used.insert({i_cnt + 2, j_cnt});
                    q.push({i_cnt + 2, j_cnt});
                }
                if (powl(primes[i], i_cnt) * powl(primes[j], j_cnt + 2) <= 1e12 && !used.contains({i_cnt, j_cnt + 2})) {
                    used.insert({i_cnt, j_cnt + 2});
                    q.push({i_cnt, j_cnt + 2});
                }
            }
        }
    }
    cerr << st.size() << endl;

    while (Q--) {
        int a;
        cin >> a;
        auto it = st.upper_bound(a);
        it--;
        cout << *it << endl;
    }
}
