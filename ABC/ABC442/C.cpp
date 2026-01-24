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
    int n, m;
    cin >> n >> m;
    vector<set<int>> rigai(n);
    vector<int> a(m), b(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        a[i]--, b[i]--;
        rigai[a[i]].insert(b[i]);
        rigai[b[i]].insert(a[i]);
    }

    for (int i = 0; i < n; i++) {
        int nokori = n - 1 - rigai[i].size();
        int ans = 1;
        for (int i = 0; i < 3; i++) {
            ans *= (nokori - i);
        }
        for (int i = 0; i < 3; i++) {
            ans /= (i + 1);
        }
        cout << ans << endl;
    }
}
