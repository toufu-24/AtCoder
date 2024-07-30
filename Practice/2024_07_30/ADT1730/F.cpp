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
    int N;
    cin >> N;
    vector<pair<int, int>> AC(N);
    map<int, int> mp;
    for (int i = 0; i < N; i++) {
        int a, c;
        cin >> a >> c;
        AC[i] = {a, c};
        if (mp.contains(c)) {
            mp[c] = min(mp[c], a);
        } else {
            mp[c] = a;
        }
    }

    int ans = 0;
    for (auto [c, a] : mp) {
        ans = max(ans, mp[c]);
    }
    cout << ans << endl;
}
