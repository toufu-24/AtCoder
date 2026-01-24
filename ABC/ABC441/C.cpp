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
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SORT(a);
    int sake_sum = 0;
    vector<pair<int, bool>> sake(n);
    for (int i = 0; i < n; i++) {
        sake[i] = {a[i], i < k};
    }
    REVERSE(sake);
    int drunk = 0;
    for (int i = 0; i < n; i++) {
        drunk += ((sake[i].second) ? sake[i].first : 0);
        if (drunk >= x) {
            cout << i + 1 << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
