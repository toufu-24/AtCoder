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
    string x, y;
    cin >> x >> y;
    vector<string> s = {"Ocelot", "Serval", "Lynx"};
    int idxx = -1, idxy = -1;
    for (int i = 0; i < 3; i++) {
        if (x == s[i]) {
            idxx = i;
        }
        if (y == s[i]) {
            idxy = i;
        }
    }
    cerr << idxx << " " << idxy << endl;
    if (idxx >= idxy) {
        cout << "Yes";
    } else {
        cout << "No";
    }
}
