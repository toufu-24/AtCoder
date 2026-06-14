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
    vector<vector<int>> a(n);
    vector<vector<int>> cnt(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
            a[i][j]--;
            // cnt[a[i][j]]++;
            cnt[a[i][j]].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << cnt[i].size() << " ";
        for (auto x : cnt[i]) {
            cout << x + 1 << " ";
        }
        cout << endl;
    }
}
