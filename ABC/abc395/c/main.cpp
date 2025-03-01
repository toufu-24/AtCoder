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
    vector<int> su(n);
    iota(all(su), 0);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        mp[i] = i;
    }

    while (q--) {
        int t;
        cin >> t;
        // 鳩 a を 巣 b に入れる
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            su[a] = mp[b];
        } else if (t == 2) {
            // 巣 a, b をswap
            int a, b;
            cin >> a >> b;
            a--, b--;
            swap(mp[a], mp[b]);
        } else if (t == 3) {
            // 鳩 a の巣を出力
            int a;
            cin >> a;
            a--;
            cout << su[a] << endl;
        }
    }
}