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
    map<int, int> cnt;
    map<int, int> idx;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        idx[a[i]] = i;
    }

    int ans = -1;
    for (auto [key, value] : cnt) {
        if (value >= 2) {
            continue;
        } else {
            ans = max(ans, key);
        }
    }
    if (ans == -1) {
        cout << -1 << endl;
        return 0;
    }
    cout << idx[ans] + 1 << endl;
}
