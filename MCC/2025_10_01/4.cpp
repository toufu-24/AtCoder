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
    vector<pair<string, string>> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i].first >> s[i].second;
    }
    map<string, vector<string>> mp;
    for (int i = 0; i < n; i++) {
        mp[s[i].first].push_back(s[i].second);
    }
    bool ans = true;
    map<string, bool> watched, finished;
    auto dfs = [&](auto dfs, string s) -> void {
        if (!ans) {
            return;
        }
        watched[s] = true;
        for (auto t : mp[s]) {
            if (finished[t]) {
                continue;
            }
            if (watched[t] && !finished[t]) {
                ans = false;
                return;
            }
            dfs(dfs, t);
        }
        finished[s] = true;
    };

    for (auto [k, v] : mp) {
        if (watched[k]) {
            continue;
        }
        dfs(dfs, k);
    }
    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}