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

using mint = modint998244353;

int32_t main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> indexes(100);
    for (int i = 0; i < n; i++) {
        indexes[s[i] - '0'].push_back(i);
    }

    vector<mint> factorial(1e7, 1);
    for (int i = 1; i < factorial.size(); i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    mint ans = 0;
    for (int i = 0; i < n; i++) {
        if (indexes[s[i] + 1 - '0'].empty() || indexes[s[i] - '0'].empty()) {
            continue;
        }
        int now_idx = lower_bound(all(indexes[s[i] - '0']), i) - (indexes[s[i] - '0']).begin();
        int now_cnt = now_idx;
        int next_idx = lower_bound(all(indexes[s[i] + 1 - '0']), i) - (indexes[s[i] + 1 - '0']).begin();
        int next_cnt = indexes[s[i] + 1 - '0'].size() - next_idx;

        int max_cnt = min(next_cnt, now_cnt);
        // sum k=1_max_cnt now_cnt Choose (k-1) * next_cnt Choose k
        // now_cnt + next_cnt Choose max_cnt ?
        int left = now_cnt + next_cnt;
        int right = now_cnt + 1;
        // cerr << left << "choose" << right << endl;
        if (left - right < 0) {
            continue;
        }

        ans += factorial[left] * factorial[left - right].inv() * factorial[right].inv();
    }

    cout << ans.val() << endl;
}
