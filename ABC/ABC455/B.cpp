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
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int ii = i; ii < h; ii++) {
                for (int jj = j; jj < w; jj++) {

                    bool ok = true;
                    for (int a = i; a <= ii; a++) {
                        for (int b = j; b <= jj; b++) {
                            ok &= (s[a][b] == s[i + ii - a][j + jj - b]);
                        }
                    }
                    ans += ok;
                }
            }
        }
    }
    cout << ans << endl;
}
