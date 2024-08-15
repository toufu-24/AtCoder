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
    vector<int> a1(3), a2(3), b1(3), b2(3);
    for (int i = 0; i < 3; i++) {
        cin >> a1[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> a2[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> b1[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> b2[i];
    }

    vector<int> a_max(3), a_min(3), b_max(3), b_min(3);
    for (int i = 0; i < 3; i++) {
        a_max[i] = max(a1[i], a2[i]);
        a_min[i] = min(a1[i], a2[i]);
        b_max[i] = max(b1[i], b2[i]);
        b_min[i] = min(b1[i], b2[i]);
    }

    bool ok = true;
    for (int i = 0; i < 3; i++) {
        if (!((a_min[i] < b_max[i] && b_min[i] < a_min[i]) || (b_min[i] < a_max[i] && a_min[i] < b_min[i]))) {
            ok = false;
        }
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
