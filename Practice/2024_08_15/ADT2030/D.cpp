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

bool check(vector<string> &a, vector<string> &b) {
    int H = a.size();
    int W = a[0].size();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int32_t main() {
    int H, W;
    cin >> H >> W;
    vector<string> a(H);
    for (int i = 0; i < H; i++) {
        cin >> a[i];
    }
    vector<string> b(H);
    for (int i = 0; i < H; i++) {
        cin >> b[i];
    }

    vector<string> c = a;
    for (int i = 0; i <= H; i++) {
        // 上シフト
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < H; k++) {
                c[k][j] = a[(k + 1) % H][j];
            }
        }
        if (check(c, b)) {
            cout << "Yes" << endl;
            return 0;
        }
        a = c;
        for (int j = 0; j < W; j++) {
            // 右シフト
            for (int k = 0; k < H; k++) {
                for (int l = 0; l < W; l++) {
                    c[k][l] = a[k][(l + 1) % W];
                }
            }
            a = c;
            if (check(c, b)) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}
