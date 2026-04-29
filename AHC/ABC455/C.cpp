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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }

    vector<int> v;
    for (auto [key, val] : mp) {
        v.push_back(key * val);
    }
    SORT(v);
    int ans = 0;
    if (k >= v.size()) {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < v.size() - k; i++) {
        ans += v[i];
    }

    cout << ans << endl;
}
