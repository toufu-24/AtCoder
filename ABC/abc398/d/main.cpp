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
    int n, r, c;
    cin >> n >> r >> c;
    string s;
    cin >> s;
    pair<int, int> pos = {0, 0};
    set<pair<int, int>> diff;
    diff.insert(pos);
    string ans;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'N') {
            pos.first--;
        } else if (s[i] == 'S') {
            pos.first++;
        } else if (s[i] == 'W') {
            pos.second--;
        } else {
            pos.second++;
        }
        diff.insert(pos);

        // {R,C} が diff に含まれているか
        if (diff.count({pos.first - r, pos.second - c})) {
            ans += to_string(1);
        } else {
            ans += to_string(0);
        }
    }
    cout << ans << endl;
}
