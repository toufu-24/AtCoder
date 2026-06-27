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
    int n = s.size();
    int e_cnt = 0;
    for (auto c : s) {
        e_cnt += (c == 'E');
    }
    if (e_cnt < n - e_cnt) {
        cout << "West" << endl;
    } else {
        cout << "East" << endl;
    }
}
