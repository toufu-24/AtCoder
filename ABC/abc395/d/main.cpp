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

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<set<int>> su(n); // 巣 i にいる鳩の集合
    for (int i = 0; i < n; i++) {
        su[i].insert(i);
    }
    vector<int> hato(n); // 鳩 i は 巣 hato[i] にいる
    for (int i = 0; i < n; i++) {
        hato[i] = i;
    }
    vector<int> conv(n); // 巣 i は 巣 conv[i] とする
    iota(all(conv), 0);
    vector<int> rev_conv(n); // 巣 conv[i] は 巣 rev_conv[i] とする
    iota(all(rev_conv), 0);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // 鳩 a を 巣 b に入れる
            int a, b;
            cin >> a >> b;
            a--, b--;
            hato[a] = rev_conv[b];
        } else if (t == 2) {
            // 巣 a, b をswap
            int a, b;
            cin >> a >> b;
            a--, b--;
            // swap(conv[conv[a]], conv[conv[b]]);
            // swap(conv[a], conv[b]);
            swap(conv[rev_conv[a]], conv[rev_conv[b]]);
            swap(rev_conv[a], rev_conv[b]);
        } else if (t == 3) {
            // 鳩 a の巣を出力
            int a;
            cin >> a;
            a--;
            cout << conv[hato[a]] + 1 << endl;
        }
    }
}