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
    string d;
    cin >> d;
    map<char, char> mp;
    mp['N'] = 'S';
    mp['S'] = 'N';
    mp['E'] = 'W';
    mp['W'] = 'E';

    for (int i = 0; i < d.size(); i++) {
        cout << mp[d[i]];
    }
    cout << endl;
}
