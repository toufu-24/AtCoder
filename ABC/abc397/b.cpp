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
    int idx = 0;
    int cnt = 0;
    while (idx < s.size()) {
        if (idx % 2 == 0) {
            if (s[idx] != 'i') {
                s.insert(idx, "i");
                cnt++;
            }
        } else {
            if (s[idx] != 'o') {
                s.insert(idx, "o");
                cnt++;
            }
        }
        idx++;
    }
    if (s.size() % 2 == 1) {
        cnt++;
    }
    cout << cnt << endl;
    cerr << s << endl;
}
