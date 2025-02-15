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

    int n = s.size();
    int ans = 0;
    for (int a = 0; a < n; a++) {
        if (s[a] != 'A')
            continue;
        for (int b = a + 1; b < n; b++) {
            if (s[b] == 'B') {
                int diff = b - a;
                if (b + diff < n && s[b + diff] == 'C') {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}
