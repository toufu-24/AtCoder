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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    int good_teinei_cnt = 0;
    for (int i = 0; i < n; i++) {
        good_teinei_cnt += (b[i] == 2);
    }

    int ans = reduce(all(a));

    priority_queue<int, vector<int>, greater<int>> good;
    priority_queue<int> bad;
    for (int i = 0; i < n; i++) {
        if (good.size() < good_teinei_cnt) {
            good.push(a[i]);
        } else {
            good.push(a[i]);
            bad.push(good.top());
            good.pop();
        }
    }

    while (q--) {
        int w, x, y;
        cin >> w >> x >> y;
        w--;
        if (b[w] == 1 && y == 2) {
            good_teinei_cnt++;
            good.push(bad.top());
            bad.pop();
        } else if (b[w] == 2 && y == 1) {
            good_teinei_cnt--;
        }
        ans -= a[w];
        ans += x;

        a[w] = x;
        b[w] = y;

        // 機嫌上位good_teinei_cntの馬の機嫌和を基本的には足せばいい
        // が，機嫌が悪くて丁寧な馬がいないときに注意しないと
    }
}
