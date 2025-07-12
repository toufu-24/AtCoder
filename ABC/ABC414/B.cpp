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
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    string ans;
    int len = 0;
    for (int i = 0; i < n; i++) {
        len += a[i].second;
        if (len > 100) {
            cout << "Too Long" << endl;
            return 0;
        }
        ans.insert(ans.end(), a[i].second, a[i].first);
    }
    cout << ans << endl;
}