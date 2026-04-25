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

    // vector<int> a_sum(n + 1, 0), b_sum(n + 1, 0), c_sum(n + 1, 0);
    vector<vector<int>> sum(n + 1, vector<int>(3, 0));
    for (int i = 0; i < n; i++) {
        sum[i + 1][0] = sum[i][0] + (s[i] == 'A');
        sum[i + 1][1] = sum[i][1] + (s[i] == 'B');
        sum[i + 1][2] = sum[i][2] + (s[i] == 'C');
    }

    // ABが同じになる個数
    // sum[r][0] - sum[l][0] == sum[r][1] - sum[l][1]
    // sum[r][0] - sum[r][1] == sum[l][0] - sum[l][1]
    vector<int> ab(n + 1, 0), bc(n + 1, 0), ca(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        ab[i] = sum[i][0] - sum[i][1];
        bc[i] = sum[i][1] - sum[i][2];
        ca[i] = sum[i][2] - sum[i][0];
    }
    int ab_cnt = 0;
    map<int, int> ab_mp;
    for (auto x : ab) {
        ab_cnt += ab_mp[x];
        ab_mp[x]++;
    }
    int bc_cnt = 0;
    map<int, int> bc_mp;
    for (auto x : bc) {
        bc_cnt += bc_mp[x];
        bc_mp[x]++;
    }
    int ca_cnt = 0;
    map<int, int> ca_mp;
    for (auto x : ca) {
        ca_cnt += ca_mp[x];
        ca_mp[x]++;
    }

    int abc_cnt = 0;
    // sum[r][0] - sum[l][0] == sum[r][1] - sum[l][1] == sum[r][2] - sum[l][2]

    // sum[r][0] - sum[r][1] == sum[l][0] - sum[l][1]
    // sum[r][0] - sum[r][2] == sum[l][0] - sum[l][2]
    // がどっちも成り立つ個数

    map<pair<int, int>, int> abc_mp;
    for (int i = 0; i <= n; i++) {
        pair<int, int> x = {ab[i], bc[i]};
        abc_cnt += abc_mp[x];
        abc_mp[x]++;
    }

    // 全体 - |a == b または b == c または c == a|
    // |a == b または b == c または c == a| = ab + bc + ca - abc - abc - abc + abc
    cout << (n * (n + 1)) / 2 - (ab_cnt + bc_cnt + ca_cnt - 2 * abc_cnt) << endl;
    cerr << ab_cnt << " " << bc_cnt << " " << ca_cnt << " " << abc_cnt;
}
