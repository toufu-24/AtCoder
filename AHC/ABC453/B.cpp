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
    int t, x;
    cin >> t >> x;
    vector<int> a(t + 1);
    for (int i = 0; i <= t; i++) {
        cin >> a[i];
    }
    vector<int> ans;
    ans.push_back(a[0]);
    cout << 0 << " " << a[0] << endl;
    for (int i = 1; i <= t; i++) {
        if (abs(ans.back() - a[i]) >= x) {
            ans.push_back(a[i]);
            cout << i << " " << a[i] << endl;
        }
    }
}
