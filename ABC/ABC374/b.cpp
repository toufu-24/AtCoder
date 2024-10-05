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
    string s, t;
    cin >> s >> t;
    int size = max(s.size(), t.size());
    while (s.size() < size) {
        s = s + '0';
    }
    while (t.size() < size) {
        t = t + '0';
    }

    assert(s.size() == t.size());
    int ans = 0;
    for (int i = 0; i < size; i++) {
        if (s[i] != t[i]) {
            ans = i + 1;
            break;
        }
    }
    cout << ans << endl;
}
