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
    map<int, int> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }

    int ans = reduce(all(a));

    int q;
    cin >> q;
    while (q--) {
        int b, c;
        cin >> b >> c;
        ans -= mp[b] * b;
        ans += mp[b] * c;
        mp[c] += mp[b];
        mp[b] = 0;
        cout << ans << endl;
    }
}
