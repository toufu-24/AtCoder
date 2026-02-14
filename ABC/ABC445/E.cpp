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

using mint = modint998244353;

// https://qiita.com/ganyariya/items/fba261ee53a5b6decc47
template <typename T>
vector<T> smallest_prime_factors(T n) {

    vector<T> spf(n + 1);
    for (int i = 0; i <= n; i++)
        spf[i] = i;

    for (T i = 2; i * i <= n; i++) {

        // 素数だったら
        if (spf[i] == i) {

            for (T j = i * i; j <= n; j += i) {

                // iを持つ整数かつまだ素数が決まっていないなら
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    return spf;
}

template <typename T>
vector<T> factolization(T x, vector<T> &spf) {
    vector<T> ret;
    while (x != 1) {
        ret.push_back(spf[x]);
        x /= spf[x];
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int32_t main() {
    int t;
    cin >> t;
    auto spf = smallest_prime_factors(10000000L);
    while (t--) {
        int n;
        cin >> n;
        // mp[val] = cnt, idx
        map<int, pair<int, int>> max_idx;
        map<int, pair<int, int>> second_idx;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            // cin >> a[i];
            int tmp;
            cin >> tmp;
            a[i] = tmp;
            if (a[i] == 1) {
                continue;
            }
            auto result = factolization(a[i], spf);
            vector<pair<int, int>> facts;
            int val = result.front();
            int cnt = 0;
            for (auto x : result) {
                if (x == val) {
                    cnt++;
                } else {
                    facts.push_back({val, cnt});
                    val = x;
                    cnt = 1;
                }
            }
            facts.push_back({val, cnt});

            for (auto [val, cnt] : facts) {
                // 最大かどうか
                if (!max_idx.contains(val) || max_idx[val].first < cnt) {
                    second_idx[val] = max_idx[val];
                    max_idx[val] = {cnt, i};
                } else if (!second_idx.contains(val) || second_idx[val].first < cnt) {
                    second_idx[val] = {cnt, i};
                }
            }
        }

        mint g = 1;
        for (auto &[p, info] : max_idx) {
            int e = info.first;  // 最大指数
            g *= mint(p).pow(e); // p^e
        }

        // cerr << "lcm = " << g.val() << endl;

        // idxについて，maxをとるval vec
        map<int, vector<int>> max_mp;
        for (auto x : max_idx) {
            max_mp[x.second.second].push_back(x.first);
            // cerr << x.second.second << " " << x.first << endl;
        }

        for (int i = 0; i < n; i++) {
            mint ans = g;
            for (auto val : max_mp[i]) {
                // cerr << ans.val() << endl;
                ans /= mint(val).pow(max_idx[val].first - second_idx[val].first);
                // cerr << ans.val() << endl;
                // cerr << val << " " << max_idx[val].first << " " << max_idx[val].second << " " << max_idx[val].second << " " << second_idx[val].second << " " << endl;
                // cerr << ((mint)max_idx[val].first * val).val() << endl;
                // cerr << ((mint)second_idx[val].first * val).val() << endl;
            }
            cout << ans.val() << " ";
        }
        cout << endl;
    }
}
