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
    int x;
    cin >> x;
    int left = 0, right = 1e9;
    while (abs(left - right) > 1) {
        int mid = (left + right) / 2;
        if ((mid * (mid + 1)) / 2 >= x) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << left + 1 << endl;
}
