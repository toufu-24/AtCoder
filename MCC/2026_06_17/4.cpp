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
    for (int a = 0; a < 1e7; a++) {
        // cerr << "a= " << a << endl;
        {
            int b5 = a * a * a * a * a - x;
            int left = 0, right = 1e3;
            while (right - left > 1) {
                int mid = (left + right) / 2;
                if (mid * mid * mid * mid * mid > b5) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            int b = left;
            // cerr << "b= " << b << endl;

            if (b * b * b * b * b == b5) {
                cout << a << " " << b << endl;
                break;
            }
        }
        {
            int b5 = a * a * a * a * a - x;
            int left = -1e3, right = 0;
            while (right - left > 1) {
                int mid = (left + right) / 2;
                if (mid * mid * mid * mid * mid < b5) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            int b = left;
            // cerr << "b= " << b << endl;
            if (b * b * b * b * b == b5) {
                cout << a << " " << b << endl;
                break;
            }
        }
        // break;
    }
}
