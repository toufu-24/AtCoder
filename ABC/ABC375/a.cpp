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
    int asn = 0;
    for (int i = 0; i < n - 2; i++) {
        if (s[i] == '#' && s[i + 1] == '.' && s[i + 2] == '#') {
            asn++;
        }
    }
    cout << asn << endl;
}
