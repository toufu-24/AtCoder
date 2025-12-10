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
    vector<int> a(n + 1, -100);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> cnt(5e5 + 10, 0);
    int same = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i == a[i]) {
            ans += same;
            same++;
        }
        else if (a[a[i]] == i && a[i] < i){
            // cerr << i << " " << a[i] << " " << a[a[i]] << endl;
            ans++;
        }
    }
    cout << ans << endl;
}
