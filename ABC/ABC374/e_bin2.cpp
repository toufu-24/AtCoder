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
    int n, x;
    cin >> n >> x;
    vector<vector<int>> apbq(n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> apbq[i][j];
        }
    }

    int ok = 0, ng = 1e18;
    while (abs(ok - ng) > 1) {
        // x円でmid個の処理ができるか
        int mid = (ok + ng) / 2;
        int remain_money = x;
        bool can = true;
        for (int i = 0; i < n; i++) {
            int a = apbq[i][0];
            int p = apbq[i][1];
            int b = apbq[i][2];
            int q = apbq[i][3];
            // sはp円でa個，tはq円でb個
            int left = 0, right = mid / a + 1; // sの個数の範囲
            while (right - left > 2) {
                int c1 = (left * 2 + right) / 3;
                int c2 = (left + right * 2) / 3;
                int cost1 = c1 * p + ((mid - c1) * a) * q;
                int cost2 = c2 * p + ((mid - c2) * a) * q;
                if (cost1 < cost2) {
                    right = c2;
                } else {
                    left = c1;
                }
            }
            int s = left;
            int t = ((mid - s * a) + b - 1) / b;
            assert(s * a + t * b >= mid);
            if (s * a >= mid) {
                t = 0;
            }
            int cost = s * p + t * q;
            remain_money -= cost;
            if (remain_money < 0) {
                can = false;
                break;
            }
        }
        if (remain_money < 0) {
            can = false;
        }

        if (can) {
            ok = mid;
        } else {
            ng = mid;
        }
    }

    cout << ok << endl;
}
