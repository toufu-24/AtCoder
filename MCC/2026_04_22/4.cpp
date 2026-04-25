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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    int now = 0;
    int susumu = 0;
    int max_susumu = 0;
    for (int i = 0; i < n; i++) {
        susumu += a[i];
        max_susumu = max(susumu, max_susumu);
        ans = max(ans, now + max_susumu);
        now += susumu;
    }
    cout << ans << endl;
}
