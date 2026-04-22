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
    int n, x;
    cin >> n >> x;
    vector<int> m(n);
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }

    int ans = 0;
    x -= reduce(all(m));
    cerr << "x= " << x << endl;
    ans += (x / *min_element(all(m)));
    ans += n;
    cout << ans << endl;
}
