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
    map<int, int> cnt;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> uptwo;
    for (auto [key, val] : cnt) {
        if (val >= 2) {
            uptwo.push_back(key);
        }
    }
    RSORT(uptwo);
    int ans = 0;
    if (uptwo.size() >= 2) {
        ans = uptwo[0] * uptwo[1];
    }
    if (uptwo.size() >= 1) {
        if (cnt[uptwo[0]] >= 4) {
            ans = max(ans, uptwo[0] * uptwo[0]);
        }
    }
    cout << ans << endl;
}
