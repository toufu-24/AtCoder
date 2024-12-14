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
    int n, r;
    cin >> n >> r;
    vector<int> d(n), a(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> a[i];
    }

    for (int i = 0; i < n; i++) {
        switch (d[i]) {
        case 1:
            if (1600 <= r && r <= 2799) {
                r += a[i];
            }
            break;
        case 2:
            if (1200 <= r && r <= 2399) {
                r += a[i];
            }
            break;
        }
    }
    cout << r << endl;
}
