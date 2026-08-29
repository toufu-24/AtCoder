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
    map<int, int> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }

    vector<int> clas;
    int ans = 0;
    for (auto [key, val] : mp) {
        clas.push_back(val);
    }
    int ma = *max_element(all(clas));
    for (auto [key, val] : mp) {
        // val + 1  のよりおおきいのがあるか
        if (val + 1 < ma) {

        } else {
            ans++;
        }
    }
    cout << ans << endl;
}
