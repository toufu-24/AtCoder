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
    vector<int> v(3);
    for (int i = 0; i < 3; i++)
        cin >> v[i];
    bool ans = false;
    SORT(v);
    if (v[0] == v[1] && v[1] == v[2])
        ans = true;
    if (v[0] + v[1] == v[2])
        ans = true;
    cout << (ans ? "Yes" : "No") << endl;
}
