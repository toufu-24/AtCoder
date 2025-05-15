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
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (__popcount(mask) <= 3) {
            continue;
        }

        vector<int> take;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                take.push_back(l[i]);
            }
        }
    }
}
