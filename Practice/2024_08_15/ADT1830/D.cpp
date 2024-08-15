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
    string s;
    cin >> s;
    vector<vector<int>> pin(7);
    pin[0] = {7}, pin[1] = {4}, pin[2] = {8, 2}, pin[3] = {1, 5}, pin[4] = {3, 9}, pin[5] = {6}, pin[6] = {10};
    bool one = false, zero = false, one2 = false;
    for (int i = 0; i < pin.size(); i++) {
        bool o = false, z = true;
        for (int j = 0; j < pin[i].size(); j++) {
            if (s[pin[i][j] - 1] == '1') {
                o = true;
                z = false;
            }
        }

        if (o && !one) {
            one = true;
        } else if (z && !zero && one) {
            zero = true;
        } else if (o && !one2 && zero) {
            one2 = true;
        }
    }

    if (one2 && s[0] == '0') {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
