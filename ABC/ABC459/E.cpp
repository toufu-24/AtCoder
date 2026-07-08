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

const int MOD = 998244353;

// https://algo-logic.info/combination/#
vector<long long> fact_inv, inv;
/*  init_nCk :二項係数のための前処理
    計算量:O(k)
*/
void init_nCk(int SIZE) {
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++) {
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
}
/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(k)
*/
mint nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    mint ans = 1;
    for (int i = n; i >= n - k + 1; i--) {
        ans *= i;
        // ans %= MOD;
    }
    return ans * fact_inv[k];
}

int32_t main() {
    init_nCk(5e6);
    int n;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<int> p(n, -1);
    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        tree[p[i]].push_back(i);
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    bool ok = true;
    mint ans = 1;
    auto dfs = [&](auto dfs, int now) -> int {
        if (!ok) {
            return 0;
        }
        int ret = 0;
        for (auto next : tree[now]) {
            ret += dfs(dfs, next);
            if (!ok) {
                return 0;
            }
        }
        ret += c[now];
        // ret C d[now]
        if (((ret < d[now])) || ((ret < 0 || d[now] < 0))) {
            ok = false;
            return 0;
        }
        ans *= nCk(ret, d[now]);

        ret -= d[now];
        return ret;
    };

    dfs(dfs, 0);
    if (!ok) {
        cout << 0 << endl;
        return 0;
    }
    cout << ans.val() << endl;
}
