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
        cerr << a[i] << " ";
    }
    cerr << endl;

    // 和が正となる区間の数え上げ
    // https://qiita.com/drken/items/ecd1a472d3a0e7db8dce#%E5%95%8F%E9%A1%8C-1aoj-course-the-number-of-windows
    int x = 0;
    /* 合計値 */
    long long res = 0;

    /* 区間の左端 left で場合分け */
    int right = 0;     // 毎回 right を使い回すようにする
    long long sum = 0; // sum も使い回す
    for (int left = 0; left < n; ++left) {
        /* sum に a[right] を加えても大丈夫なら right を動かす */
        while (right < n && sum + a[right] <= x) {
            sum += a[right];
            ++right;
        }

        /* break した状態で right は条件を満たす最大 */
        res += (right - left);
        cerr << left << " " << right << endl;

        /* left をインクリメントする準備 */
        if (right == left)
            ++right; // right が left に重なったら right も動かす
        else
            sum -= a[left]; // left のみがインクリメントされるので sum から a[left] を引く
    }

    cerr << (n * (n + 1) / 2) << endl;
    cerr << res << endl;
    cout << (n * (n + 1) / 2) - res << endl;
}
