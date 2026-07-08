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
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        vector<int> cnt(26, 0);
        for (auto c : s) {
            cnt[c - 'a']++;
        }
        int max_cnt = 0;
        int max_idx = 0;
        for (int i = 0; i < 26; i++) {
            if (max_cnt <= cnt[i]) {
                max_cnt = cnt[i];
                max_idx = i;
            }
        }
        string tmp = "";
        for (int i = 0; i < 26; i++) {
            if (max_idx != i) {
                for (int j = 0; j < cnt[i]; j++) {
                    tmp.push_back(i + 'a');
                }
            }
        }

        // 2->1
        // 3->2
        // 4->2
        // 5->3
        if ((s.size() + 1) / 2 >= max_cnt) {
            cout << "Yes" << endl;
            int n = s.size();
            string ans = "";
            int idx = 0;
            while (max_cnt--) {
                ans += max_idx + 'a';
                ans += tmp[idx];
            }
            while (idx < tmp.size()) {
                ans
            }

        } else {
            cout << "No" << endl;
        }
    }
}
