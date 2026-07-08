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
    map<int, vector<int>> mp;
    vector<int> a(n), d(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> d[i] >> b[i];
        d[i]--;
        a[i]--, b[i]--;
        if (a[i] != b[i]) {
            mp[d[i]].push_back(i);
        }
    }

    map<int, int> color;
    for (int i = 0; i < n; i++) {
        color[a[i]]++;
    }

    for (int i = 0; i < m; i++) {
        auto change = mp[i];
        for (auto idx : change) {
            color[a[idx]]--;
            if (color[a[idx]] == 0) {
                color.erase(a[idx]);
            }
            color[b[idx]]++;
        }
        cout << color.size() << endl;
    }
}
