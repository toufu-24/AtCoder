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
    int prev = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') {
            if (prev == -1) {
                prev = i;
            } else {
                cout << prev + 1 << "," << i + 1 << endl;
                prev = -1;
            }
        }
    }
}
