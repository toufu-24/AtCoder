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
    if (s == "red") {
        cout << "SSS" << endl;
    } else if (s == "blue") {
        cout << "FFF" << endl;
    } else if (s == "green") {
        cout << "MMM" << endl;
    } else {
        cout << "Unknown" << endl;
    }
}
