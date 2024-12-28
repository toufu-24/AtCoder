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
    int k;
    cin >> k;
    string s, t;
    cin >> s >> t;
    if (s.size() > t.size()) {
        swap(s, t);
    }
    bool ok = false;
    if (s.size() == t.size()) {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                cnt++;
            }
        }
        ok = ((cnt == 1) || (s == t));
    } else if (s.size() + 1 == t.size()) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                s.insert(i, 1, t[i]);
                break;
            }
        }
        if(s.size() != t.size()) {
            s += t.back();
        }
        ok = (s == t);
    }
    cout << (ok ? "Yes" : "No") << endl;
}
