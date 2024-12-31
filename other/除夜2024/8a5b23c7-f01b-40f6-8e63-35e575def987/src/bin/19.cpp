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
    char c1, c2;
    cin >> c1 >> c2;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] != c1) {
            cout << c2;
        } else {
            cout << s[i];
        }
    }
}
