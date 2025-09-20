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
    set<int> a;
    for (int i = 0; i < 3; i++) {
        int b;
        cin >> b;
        a.insert(b);
    }
    if (a.size() <= 2) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
