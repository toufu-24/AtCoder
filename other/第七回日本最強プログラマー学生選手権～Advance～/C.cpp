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
    int n, q;
    cin >> n >> q;
    vector<int> place(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        place[p[i]] = i;
    }

    int cnt = n;
    while (q--) {
        int a;
        cin >> a;
        a--;
        place[a] = cnt;
        cnt++;
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        ans.push_back({place[i], i});
    }
    SORT(ans);

    for (auto [p, val] : ans) {
        cout << val + 1 << " ";
    }
}
