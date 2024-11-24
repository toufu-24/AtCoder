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
    int v, a, b, c;
    cin >> v >> a >> b >> c;
    vector<int> sam = {a, b, c};
    int ans = 0;
    while (v >= 0) {
        v -= sam[ans % 3];
        ans++;
    }
    ans--;
    if (ans % 3 == 0)
        cout << "F" << endl;
    else if (ans % 3 == 1)
        cout << "M" << endl;
    else
        cout << "T" << endl;
}
