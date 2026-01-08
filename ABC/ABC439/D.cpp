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
    vector<int> a(n);
    vector<int> three, five, seven;
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 3 == 0) {
            three.push_back(i);
        }
        if (a[i] % 5 == 0) {
            five.push_back(i);
        }
        if (a[i] % 7 == 0) {
            seven.push_back(i);
        }
        mp[a[i]].push_back(i);
    }

    int ans = 0;
    // five基準で考える
    for (int i = 0; i < five.size(); i++) {
        int f_idx = five[i];
        int f_val = a[f_idx];
        assert(f_val % 5 == 0);
        int kijyun = f_val / 5;
        // kijyun * 7 で，f_idx
        int s_val = kijyun * 7;
        int s_tmp_idx = lower_bound(all(mp[s_val]), f_idx) - mp[s_val].begin();
        int s_lower_num = s_tmp_idx;
        int s_upper_num = mp[s_val].size() - s_tmp_idx;
        // kijyun * 3 で，f_idx
        int t_val = kijyun * 3;
        int t_tmp_idx = lower_bound(all(mp[t_val]), f_idx) - mp[t_val].begin();
        int t_lower_num = t_tmp_idx;
        int t_upper_num = mp[t_val].size() - t_tmp_idx;

        ans += s_upper_num * t_upper_num; // min = j
        ans += s_lower_num * t_lower_num; // max = j
    }
    cout << ans << endl;
}
