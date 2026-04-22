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
    vector<int> d1(n), d2(n);
    for (int i = 0; i < n; i++) {
        cin >> d1[i] >> d2[i];
    }

    bool ok = false;
    for (int i = 2; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < 3; j++) {
            cnt += (d1[i - j] == d2[i - j]);
        }

        if (cnt >= 3) {
            ok = true;
        }
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
