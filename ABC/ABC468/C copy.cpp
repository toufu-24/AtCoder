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
    int right = 0;
    int bad = 0;
    int circle = 0;
    for (int k = 0; k < n; k++) {
        if (s[k] == 'x') {
            if (bad < circle) {
                right++;
            }
            bad++;
        }
        if (s[k] == 'o') {
            right++;
            circle++;
        }
        while (right < n) {
            if (s[right] == 'o') {
                right++;
            } else {
                break;
            }
        }
        cout << min(right + 1, n) << endl;
        right = max(k + 1, right);
    }
}
