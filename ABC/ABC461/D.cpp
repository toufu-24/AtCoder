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

// https://algo-logic.info/submatrix-sum-queries/#
// 前処理を行う
void pre_process(vector<vector<int>> const &a, vector<vector<int>> &S) {
    int H = (int)a.size();
    int W = (int)a[0].size();
    S.assign(H + 1, vector<int>(W + 1));
    for (int h = 1; h < H + 1; h++) {
        for (int w = 1; w < W + 1; w++) {
            S[h][w] = a[h - 1][w - 1] + S[h][w - 1] + S[h - 1][w] - S[h - 1][w - 1];
        }
    }
}
// [h1,h2)×[w1,w2) の区間和を求める
int query(int h1, int h2, int w1, int w2, vector<vector<int>> const &S) {
    return S[h2][w2] - S[h1][w2] - S[h2][w1] + S[h1][w1];
}

int32_t main() {
    int h, w, k;
    cin >> h >> w >> k;
    vector<vector<int>> a(h, vector<int>(w)), sum;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
        cin >> s[i];
        for (int j = 0; j < w; j++) {
            a[i][j] = (s[i][j] - '0');
        }
    }

    pre_process(a, sum);

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int ii = i + 1; ii <= h; ii++) {
            // 高さがi~iiの長方形
            for (int j = 0; j < w; j++) {
                // 右端がどこまでいけるか
                int rleft = j, rright = w + 1;
                while (abs(rright - rleft) > 1) {
                    int mid = (rleft + rright) / 2;
                    int val = query(i, ii, j, mid, sum);
                    if (val <= k) {
                        rleft = mid;
                    } else {
                        rright = mid;
                    }
                }

                // 左端がどこまでいけるか
                int left = j, right = w + 1;
                while (abs(right - left) > 1) {
                    int mid = (left + right) / 2;
                    int val = query(i, ii, j, mid, sum);
                    if (val < k) {
                        left = mid;
                    } else {
                        right = mid;
                    }
                }
                // cerr << i + 1 << " " << ii << " " << j + 1 << " " << right << " " << rright - 1 << endl;
                ans += rright - right;
            }
        }
    }
    cout << ans << endl;
}
