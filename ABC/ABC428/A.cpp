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
    int s, a, b, x;
    cin >> s >> a >> b >> x;
    int ans = 0;
    int time = 0;
    bool run = true;
    for (int i = 0; i < x; i++) {
        time++;

        if (run) {
            ans += s;
            if (time == a) {
                run = false;
                time = 0;
            }
        } else {
            if (time == b) {
                run = true;
                time = 0;
            }
        }
    }
    cout << ans << endl;
}
