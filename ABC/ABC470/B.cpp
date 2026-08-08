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
    vector<int> c(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        mp[c[i]]++;
    }

    int max_v = 0;
    int max_k = -1;
    for (auto [key, val] : mp) {
        // max_v = max(max_v, val);
        // max_k=
        if (max_v < val) {
            max_v = val;
            max_k = key;
        }
    }

    int ans = 0;
    for (auto [key, val] : mp) {
        if(key != max_k){
            ans += val;
        }
    }
    cout << ans << endl;
}
