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
    vector<vector<int>> cnt(10, vector<int>(26, 0));
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        b[i]--;
    }

    int m;
    cin >> m;
    vector<string> s(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        for (int j = 0; j < s[i].size(); j++) {
            cnt[j][s[i][j] - 'a']++;
        }
    }

    for (int i = 0; i < m; i++) {
        bool ok = true;
        for (int j = 0; j < s[i].size(); j++) {
        }
    }
}
