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
    vector<int> su(n); // 鳩 i は 巣 su[i] にいる
    iota(all(su), 0);
    vector<int> conv(n); // 巣 i は 巣 conv[i] とする
    iota(all(conv), 0);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // 鳩 a を 巣 b に入れる
            int a, b;
            cin >> a >> b;
            a--, b--;
            su[a] = b;
        } else if (t == 2) {
            // 巣 a, b をswap
            int a, b;
            cin >> a >> b;
            a--, b--;
            swap(conv[a], conv[b]);
        } else if (t == 3) {
            // 鳩 a の巣を出力
            int a;
            cin >> a;
            a--;
            cout << conv[su[a]] + 1 << endl;
        }
    }
}