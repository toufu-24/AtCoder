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

int op(int a, int b) {
    return a + b;
}

int e() {
    return 0;
}

int32_t main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            a[i] = 1;
        } else if (s[i] == 'B') {
            a[i] = -1;
        } else {
            a[i] = 0;
        }
    }

    // 和が正となる区間の数え上げ
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }

    segtree<int, op, e> seg(1e6 + 1000);
    int margin = 5e5 + 10;
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        // st内でsum[i] - sum[j] >= 1となるjの個数
        // sum[i] - 1 >= sum[j]
        int cnt = seg.prod(0, sum[i] + margin);
        ans += cnt;
        seg.set(sum[i] + margin, seg.get(sum[i] + margin) + 1);
    }
    cout << ans << endl;
}
