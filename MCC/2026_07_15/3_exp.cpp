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
    for (int n = 0; n <= 100; n++) {
        vector<int> v(6);
        for (int i = 0; i < 6; i++) {
            v[i] = (i) % 6 + 1;
        }

        for (int i = 0; i < n; i++) {
            swap(v[i % 5], v[(i) % 5 + 1]);
        }

        for (auto x : v) {
            cout << x;
        }
        cout << endl;
    }
}
