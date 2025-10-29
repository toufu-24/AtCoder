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
    int n, t;
    cin >> n >> t;
    vector<int> people(n);
    for (int i = 0; i < n; i++) {
        cin >> people[i];
    }
    int now = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (people[i] + t) - max(people[i], now);
        now = people[i] + t;
    }
    cout << ans << endl;
}
