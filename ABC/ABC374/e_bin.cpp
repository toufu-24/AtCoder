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
            int min_cost = 1e18;
            int s = (mid + a - 1) / a;
            int s_only_cost = p * s;
            if (s_only_cost < 0) {
                s_only_cost = 1e18;
            }
            int over = s * a - mid;

            int t = (mid + b - 1) / b;
            int t_only_cost = q * t;
            if (t_only_cost < 0) {
                t_only_cost = 1e18;
            }
            min_cost = min(s_only_cost, t_only_cost);

            int s_need = mid - a;
            // s_needだけtを買ってsを買う
            int s_t_need = (s_need + b - 1) / b;
            int s_t_cost = q * s_t_need + p;
            if (s_t_cost < 0) {
                s_t_cost = 1e18;
            }
            min_cost = min(min_cost, s_t_cost);

            int t_need = mid - b;
            // t_needだけsを買ってtを買う
            int t_ = (t_need + a - 1) / a;
            int t_s_cost = p * t_ + q;
            if (t_s_cost < 0) {
                t_s_cost = 1e18;
            }
            min_cost = min(min_cost, t_s_cost);

            remain_money -= min_cost;
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
