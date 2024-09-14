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
    char sab, sac, sbc;
    cin >> sab >> sac >> sbc;
    if (sab == '>') {
        if (sac == '>') {
            if (sbc == '>') {
                cout << 'B' << endl;
            } else {
                cout << 'C' << endl;
            }
        }
        else {
            cout << 'A' << endl;
        }
    }
    else {
        // B > A
        if (sac == '>') {
            cout << 'A' << endl;
        }
        else {
            // C > A
            if (sbc == '>') {
                // B > C > A
                cout << 'C' << endl;
            } else {
                cout << 'B' << endl;
            }
        }
    }
}
