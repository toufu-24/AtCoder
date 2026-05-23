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
    int h, w;
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        bool all = (i == 0 || i == h - 1);
        for (int j = 0; j < w; j++) {
            if (all) {
                cout << '#';
            } else {
                if (j == 0 || j == w - 1) {
                    cout << '#';
                } else {
                    cout << '.';
                }
            }
        }
        cout << endl;
    }
}
