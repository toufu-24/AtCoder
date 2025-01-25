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
    int cnt = 0;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (s[j][i] == '#') {
                cnt++;
            }
        }
    }
    if (cnt == 0) {
        cout << "Yes" << endl;
        return 0;
    }

    pair<int, int> left_top, left_bottom, right_top, right_bottom;
    for (int i = 0; i < h; i++) {
        bool ok = false;
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                left_top = {i, j};
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }
    for (int i = 0; i < h; i++) {
        bool ok = false;
        for (int j = w - 1; j >= 0; j--) {
            if (s[i][j] == '#') {
                right_top = {i, j};
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }
    for (int i = h - 1; i >= 0; i--) {
        bool ok = false;
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                left_bottom = {i, j};
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }
    for (int i = h - 1; i >= 0; i--) {
        bool ok = false;
        for (int j = w - 1; j >= 0; j--) {
            if (s[i][j] == '#') {
                right_bottom = {i, j};
                ok = true;
                break;
            }
        }
        if (ok) {
            break;
        }
    }

    bool ok = true;
    int top = min(left_top.first, right_top.first);
    int bottom = max(left_bottom.first, right_bottom.first);
    int left = min(left_top.second, left_bottom.second);
    int right = max(right_top.second, right_bottom.second);
    for (int i = top; i <= bottom; i++) {
        for (int j = left; j <= right; j++) {
            if (s[i][j] == '.') {
                ok = false;
            }
        }
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cerr << left_top.first << " " << left_top.second << endl;
    cerr << right_top.first << " " << right_top.second << endl;
    cerr << left_bottom.first << " " << left_bottom.second << endl;
    cerr << right_bottom.first << " " << right_bottom.second << endl;
}
