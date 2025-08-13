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
    vector<pair<int, string>> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].first >> a[i].second;
    }
    map<int, pair<bool, int>> mp;
    for (int i = 0; i < m; i++) {
        if (mp[a[i].first].first) {
            continue;
        }
        if (a[i].second == "AC") {
            mp[a[i].first] = {true, mp[a[i].first].second};
        } else {
            mp[a[i].first] = {false, mp[a[i].first].second + 1};
        }
    }

    int ac = 0, pena = 0;
    for (auto [key, value] : mp) {
        if (value.first) {
            ac++;
            pena += value.second;
        }
    }
    cout << ac << " " << pena << endl;
}
