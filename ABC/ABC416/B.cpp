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
    string t = s;
    if (t[0] != '#') {
        t[0] = 'o';
    }
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == '#') {
            if (t[i + 1] != '#') {
                t[i + 1] = 'o';
            }
        }
    }
    cout << t << endl;
}
