#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

// #define int ll

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        string s;
        cin >> s;
        vector<vector<int>> g(n), rev_g(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            rev_g[v].push_back(u);
        }
        // 基本的にBobが勝ちそう
        // Aにしかいけない頂点に誘導したらAlice
        unordered_set<int> good_vs;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'A') {
                good_vs.insert(i);
            }
        }
        int turn = 2 * k;
        while (turn != 0) {
            // 偶数 -> Bob，奇数->Alice
            unordered_set<int> good_vs_next;
            if (turn % 2 == 0) { // Bob
                unordered_set<int> kouho;
                for (auto v : good_vs) {
                    for (auto u : rev_g[v]) {
                        kouho.insert(u);
                    }
                }
                for (auto v : kouho) {
                    bool ok = true;
                    for (auto u : g[v]) {
                        if (!good_vs.contains(u)) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        good_vs_next.insert(v);
                    }
                }
            } else { // Alice
                unordered_set<int> kouho;
                for (auto v : good_vs) {
                    for (auto u : rev_g[v]) {
                        kouho.insert(u);
                    }
                }
                for (auto v : kouho) {
                    bool ok = false;
                    for (auto u : g[v]) {
                        if (good_vs.contains(u)) {
                            ok = true;
                            break;
                        }
                    }
                    if (ok) {
                        good_vs_next.insert(v);
                    }
                }
            }
            good_vs = good_vs_next;
            turn--;
        }
        if (good_vs.contains(0)) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
}
