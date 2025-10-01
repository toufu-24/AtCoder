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
    vector<vector<int>> a(n, vector<int>(3));
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        switch (a[i][0]) {
        case 1:
            break;
        case 2:
            a[i][2]--;
            break;
        case 3:
            a[i][1]++;
            break;
        case 4:
            a[i][2]--;
            a[i][1]++;
            break;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int il = a[i][1], ir = a[i][2], jl = a[j][1], jr = a[j][2];
            if (il > jl) {
                swap(il, jl);
                swap(ir, jr);
            }

            if (jl <= ir) {
                ans++;
                cerr << i << " " << j << endl;
            }
        }
    }
    cout << ans << endl;
}