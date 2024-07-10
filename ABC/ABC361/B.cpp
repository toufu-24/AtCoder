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
    vector<int> a_1(3), a_2(3);
    for (int i = 0; i < 3; i++) {
        cin >> a_1[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> a_2[i];
    }
    vector<int> b_1(3), b_2(3);
    for (int i = 0; i < 3; i++) {
        cin >> b_1[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> b_2[i];
    }

    vector<int> a_min(3), a_max(3), b_min(3), b_max(3);
    for (int i = 0; i < 3; i++) {
        a_min[i] = min(a_1[i], a_2[i]);
        a_max[i] = max(a_1[i], a_2[i]);
        b_min[i] = min(b_1[i], b_2[i]);
        b_max[i] = max(b_1[i], b_2[i]);
    }

    bool ans = true;
    for (int i = 0; i < 3; i++) {
        if (!(b_min[i] < a_max[i] && a_min[i] < b_min[i]) && !(a_min[i] < b_max[i] && b_min[i] < a_min[i])) {
            ans = false;
            break;
        }
    }

    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
