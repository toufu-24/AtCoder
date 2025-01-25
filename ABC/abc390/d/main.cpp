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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int all_xor = 0;
    for (int i = 0; i < n; i++) {
        all_xor ^= a[i];
    }
    set<int> now;
    for (int i = 0; i < n; i++) {
        set<int> next;
        for (auto x : now) {
            next.insert(x ^ a[i]);
        }
    }
}
