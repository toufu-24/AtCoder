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
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
    }
    vector<int> ab(m);
    for (int i = 0; i < m; i++) {
        ab[i] = (a[i] + b[i]) % n;
    }
    map<int, int> cnt;
    for (int i = 0; i < m; i++) {
        cnt[ab[i]]++;
    }
    int ans = m * (m - 1) / 2;
    for (auto [key, value] : cnt) {
        ans -= value * (value - 1) / 2;
    }
    cout << ans << endl;
}
