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
    s.push_back('x');
    REVERSE(s);
    s.push_back('x');
    REVERSE(s);
    n += 2;
    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        if (s[i - 1] == 'x' && s[i] == 'x' && s[i + 1] == 'x') {
            ans++;
        }
    }
    cout << ans << endl;
}
