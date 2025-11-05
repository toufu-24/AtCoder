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
    string s;
    cin >> s;
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1') {
            ans += (1L << (s.size() - i - 1));
        }
    }

    if (ans > n) {
        cout << "-1" << endl;
        return 0;
    }

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '?') {
            ans += (1L << (s.size() - i - 1));
            if (ans <= n) {
                continue;
            } else {
                ans -= (1L << (s.size() - i - 1));
            }
        }
    }

    cout << ans << endl;
}
