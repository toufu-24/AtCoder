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
    int n, d;
    cin >> n >> d;
    vector<vector<int>> x(n, vector<int>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> x[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist2 = 0;
            for (int k = 0; k < d; k++) {
                dist2 += (x[i][k] - x[j][k]) * (x[i][k] - x[j][k]);
            }
            if (round(sqrtl(dist2)) * round(sqrtl(dist2)) == dist2) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}
