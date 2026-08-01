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
    vector<string> v = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    int idx = 0;
    for (auto c : v) {
        idx++;
        if (c == s) {
            cout << 7 - idx + 1 << endl;
            break;
        }
    }
}
