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
    map<int, int> mp, cnt;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        mp[a[i]] += b[i];
        cnt[a[i]]++;
    }

    cout << fixed << setprecision(10);

    for (auto [x, v] : mp) {
        cout << double(v) / cnt[x] << endl;
    }
}
