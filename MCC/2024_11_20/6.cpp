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
    string ans = "UNRESTORABLE";
    for (int i = s.size() - 1; i >= 0; i--) {
        int last = i;
        int start = i - t.size() + 1;
        if (start < 0) {
            continue;
        }
        bool ok = true;
        for (int j = 0; j < t.size(); j++) {
            if (start + j >= s.size()) {
                ok = false;
                break;
            }
            if (s[start + j] != t[j] && s[start + j] != '?') {
                ok = false;
                break;
            }
        }
        if (ok) {
            ans = s;
            for (int j = 0; j < t.size(); j++) {
                ans[start + j] = t[j];
            }
            for (int j = 0; j < ans.size(); j++) {
                if (ans[j] == '?')
                    ans[j] = 'a';
            }
            break;
        }
    }
    cout << ans << endl;
}
