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
    set<int> can_use;
    for (int i = 0; i < n; i++) {
        can_use.insert(i);
    }

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        can_use.erase(a[i]);
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i] == a[i + 1]) {
            ans++;
            a[i] = *can_use.begin();
            can_use.erase(can_use.begin());
        } else {
            can_use.erase(a[i]);
        }
    }
    cout << ans << endl;
}
