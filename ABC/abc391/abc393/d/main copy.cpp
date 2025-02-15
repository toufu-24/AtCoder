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
    string s;
    cin >> s;
    int mid_idx = 0;
    int one_cnt = 0;
    vector<int> one_idx;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            mid_idx += i;
            one_cnt++;
            one_idx.push_back(i);
        }
    }
    mid_idx = mid_idx / one_cnt;
    cerr << mid_idx << endl;
    vector<int> kouho_diff;
    // one_idxとmid_idxの差が小さい4つを選ぶ
    for (int i = 0; i < one_cnt; i++) {
        kouho_diff.push_back(abs(one_idx[i] - mid_idx));
    }
    SORT(kouho_diff);
    vector<int> kouho;
    for (int i = 0; i < min(2L, one_cnt); i++) {
        for (int j = 0; j < one_cnt; j++) {
            if (abs(one_idx[j] - mid_idx) == kouho_diff[i]) {
                kouho.push_back(one_idx[j]);
                break;
            }
        }
    }

    int ans = 1e9;
    for (int j = 0; j < kouho.size(); j++) {
        int idx = kouho[j];
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if (mid_idx == i) {
                    continue;
                }
                // ans += abs(idx - i) - 1;
                tmp += abs(idx - i) - 1;
            }
        }
        ans = min(ans, tmp);
    }
    cout << ans << endl;
}
