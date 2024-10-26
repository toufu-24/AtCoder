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
    vector<string> s(8);
    for (int i = 0; i < 8; i++) {
        cin >> s[i];
    }

    vector<string> t(8, string(8, '.'));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (s[i][j] == '#') {
                for (int ni = 0; ni < 8; ni++) {
                    t[ni][j] = '#';
                }
                for (int nj = 0; nj < 8; nj++) {
                    t[i][nj] = '#';
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (t[i][j] == '.') {
                ans++;
            }
        }
    }
    cout << ans << endl;
}
