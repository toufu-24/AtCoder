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
    int ans = 1e18;
    vector<int> a, b;
    for (int i = 0; i < 2 * n; i++) {
        if (s[i] == 'A') {
            a.push_back(i);
        } else {
            b.push_back(i);
        }
    }

    // ABA...
    int tmp = 0;
    int a_idx = 0, b_idx = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            tmp += abs(a[a_idx] - i);
            a_idx++;
        } else {
            tmp += abs(b[b_idx] - i);
            b_idx++;
        }
    }
    ans = min(ans, tmp);

    // BAB...
    tmp = 0;
    a_idx = 0, b_idx = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (i % 2 == 0) {
            tmp += abs(b[b_idx] - i);
            b_idx++;
        } else {
            tmp += abs(a[a_idx] - i);
            a_idx++;
        }
    }
    ans = min(ans, tmp);

    cout << ans / 2 << endl;
}
