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
    int a, b, x;
    cin >> a >> b >> x;
    int left = 0, right = int(1e9 + 1);
    while (abs(left - right) > 1) {
        // cout << left << " " << right << endl;
        int mid = (left + right) / 2;
        string mid_st = to_string(mid);
        // cout << x << " " << a * mid + b * mid_st.size() << endl;
        if (x >= a * mid + b * mid_st.size()) {
            left = mid;
        } else {
            right = mid;
        }
    }
    cout << left << endl;
}
