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
    string s1, s2;
    cin >> s1 >> s2;
    if (s1 == "sick" && s2 == "sick") {
        cout << 1 << endl;
    } else if (s1 == "sick" && s2 == "fine") {
        cout << 2 << endl;
    } else if (s1 == "fine" && s2 == "sick") {
        cout << 3 << endl;
    } else {
        cout << 4 << endl;
    }
}