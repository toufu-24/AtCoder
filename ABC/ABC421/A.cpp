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
    int n;
    cin >> n;
    vector<string> s(n);
    map<int, string> mp;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        mp[i + 1] = s[i];
    }
    int x;
    string y;
    cin >> x >> y;
    if (mp[x] == y) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
