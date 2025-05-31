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
    vector<int> l(m), r(m);
    vector<int> imos(n + 1, 0);
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
        imos[l[i]]++;
        imos[r[i] + 1]--;
    }
    for (int i = 1; i <= n; i++) {
        imos[i] += imos[i - 1];
    }
    imos.pop_back();
    int ans = *min_element(all(imos));
    cout << ans << endl;
}
