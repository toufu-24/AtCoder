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
    int h, w, n;
    cin >> h >> w >> n;
    string t;
    cin >> t;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    map<char, pair<int, int>> mp;
    mp['L'] = {0, -1};
    mp['R'] = {0, +1};
    mp['U'] = {-1, 0};
    mp['D'] = {+1, 0};

    vector<vector<bool>> reached(h, vector<bool>(w, false));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                continue;
            }
            bool ok = true;
            int ni = i, nj = j;
            for (int k = 0; k < t.size(); k++) {
                ni = ni + mp[t[k]].first;
                nj = nj + mp[t[k]].second;
                if (s[ni][nj] == '#') {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                reached[i][j] = true;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ans += reached[i][j];
            // cerr << reached[i][j] << " ";
        }
        // cerr << endl;
    }
    cout << ans << endl;
}
