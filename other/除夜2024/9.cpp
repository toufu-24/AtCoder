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
    int cnt = 0;
    bool first = true;
    for (auto c : s) {
        if (c == '-') {
            cnt++;
        } else {
            if (!first) {
                cout << cnt << " ";
            }
            cnt = 0;
            first = false;
        }
    }
}
