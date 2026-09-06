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
    string s;
    cin >> s;
    vector<int> bads;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'x') {
            bads.push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if ((bads.size()) > i) {
            cout << bads[i] + 1 << endl;
        } else {
            cout << n << endl;
        }
    }
}