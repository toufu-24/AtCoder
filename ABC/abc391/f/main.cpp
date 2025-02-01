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
    int n, k;
    cin >> n >> k;
    set<pair<int, int>> large_val;
    vector<vector<int>> abc(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> abc[i][j];
            large_val.insert({abc[i][j], i});
        }
    }
}
