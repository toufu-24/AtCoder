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
    char c = 'A';
    int now = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            now = i;
            c++;
            break;
        }
    }
    int ans = 0;
    while (c != 'Z' + 1) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                ans += abs(i - now);
                now = i;
                c++;
                break;
            }
        }
    }
    cout << ans << endl;
}
