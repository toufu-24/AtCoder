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
    int up, down, left, right;
    for (int i = 0; i < h; i++) {
        bool all = true;
        for (int j = 0; j < w; j++) {
            all &= (s[i][j] == '.');
        }
        if (!all) {
            up = i;
            break;
        }
    }
    for (int i = h - 1; i >= 0; i--) {
        bool all = true;
        for (int j = 0; j < w; j++) {
            all &= (s[i][j] == '.');
        }
        if (!all) {
            down = i;
            break;
        }
    }
    for (int i = 0; i < w; i++) {
        bool all = true;
        for (int j = 0; j < h; j++) {
            all &= (s[j][i] == '.');
        }
        if (!all) {
            left = i;
            break;
        }
    }
    for (int i = w - 1; i >= 0; i--) {
        bool all = true;
        for (int j = 0; j < h; j++) {
            all &= (s[j][i] == '.');
        }
        if (!all) {
            right = i;
            break;
        }
    }

    for (int i = 0; i < h; i++) {
        if (i < up || down < i) {
            continue;
        }
        for (int j = 0; j < w; j++) {
            if (j < left || right < j) {
                continue;
            }
            cout << s[i][j];
        }
        cout << endl;
    }
}
