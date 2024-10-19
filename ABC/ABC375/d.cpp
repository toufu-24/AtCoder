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
    vector<vector<int>> ch(26);
    for (int i = 0; i < s.size(); i++) {
        ch[s[i] - 'A'].push_back(i);
    }

    int ans = 0;
    for (int i = 0; i < 26; i++) {
        int idx_sum = 0;
        for (int j = 0; j < ch[i].size(); j++) {
            idx_sum += ch[i][j];
            int tmp = ch[i][j] * j - (idx_sum - ch[i][j]) - j;
            ans += tmp;
        }
    }
    cout << ans << endl;
}
