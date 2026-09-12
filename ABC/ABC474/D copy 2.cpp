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
    string s;
    cin >> s;
    map<char, vector<int>> mp;
    for (int i = 0; i < s.size(); i++) {
        mp[s[i]].push_back(i);
    }

    vector<vector<int>> same(mp.size());
    int idx = 0;
    for (auto [key, val] : mp) {
        // same[idx]
        for (auto x : val) {
            same[idx].push_back(x);
        }
        idx++;
    }

    int si = 7;
    // 長さ si の十進数
    for (int i = 1; i < 1e7; i++) {
        string ist = to_string(i);
        if (ist.size() > si) {
            break;
        }
        if (ist.front() == '0') {
            continue;
        }
        REVERSE(ist);
        string nokozero = string(si - ist.size(), '0');
        ist += nokozero;
        REVERSE(ist);

        // istがsを満たしているか
    }
}
// 1000000