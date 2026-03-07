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
    vector<int> c(m);
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
    }

    vector<int> kosho(m, 0);
    for (int i = 0; i < n; i++) {
        int tmp = min(c[a[i]], b[i]);
        kosho[a[i]] += tmp;
        c[a[i]] -= tmp;
    }

    cout << reduce(all(kosho)) << endl;
}
