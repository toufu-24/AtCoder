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
    vector<int> L(m), R(m);
    for (int i = 0; i < m; i++) {
        cin >> L[i] >> R[i];
    }

    cout << max(0L, *min_element(all(R)) - *max_element(all(L)) + 1) << endl;
}