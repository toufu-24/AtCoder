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
    int n, s;
    cin >> n >> s;
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    t.insert(t.begin(), 0);
    n++;
    bool ok = true;
    for (int i = 1; i < n; i++) {
        if (t[i] - t[i - 1] > s) {
            ok = false;
        }
    }
    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
