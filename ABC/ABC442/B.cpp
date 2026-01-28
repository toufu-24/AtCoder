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
    int q;
    cin >> q;
    int ans = 0;
    bool stop = true;
    vector<int> a(q);
    for (int i = 0; i < q; i++) {
        cin >> a[i];
        if (a[i] == 1) {
            ans++;
        } else if (a[i] == 2) {
            ans--;
            ans = max(0L, ans);
        } else {
            stop = !stop;
        }

        if (!stop && ans >= 3) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
