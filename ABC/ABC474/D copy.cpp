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

    int si = same.size();
    // 長さ si の十進数
    for (int i = 0; i < 1e7; i++) {
        string ist = to_string(i);
        vector<int> mappin(s.size(), -1);
        
    }
}
// 1000000