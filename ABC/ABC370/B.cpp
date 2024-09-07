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
    for (int i = 0; i < n; i++) {
        a[i].resize(i + 1);
        for (int j = 0; j < a[i].size(); j++) {
            cin >> a[i][j];
            a[i][j]--;
        }
    }

    int now = 0;
    for (int i = 0; i < n; i++) {
        int small = min(now, i), big = max(now, i);
        now = a[big][small];
    }
    cout << now + 1 << endl;
}
