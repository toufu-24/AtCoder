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

using mint = modint998244353;

int32_t main() {
    int n;
    cin >> n;
    vector<int> u(n), d(n), l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> u[i] >> d[i] >> l[i] >> r[i];
        u[i]--, d[i]--, l[i]--, r[i]--;
    }

    vector<vector<int>> sky(2001, vector<int>(2001, 0));
    vector<vector<mint>> skymod(2001, vector<mint>(2001, 1));
    int id = 2;
    for (int i = 0; i < n; i++) {
        sky[u[i]][l[i]] += id;
        sky[u[i]][r[i] + 1] -= id;
        sky[d[i] + 1][l[i]] -= id;
        sky[d[i] + 1][r[i] + 1] += id;

        skymod[u[i]][l[i]] *= id;
        skymod[u[i]][r[i] + 1] /= id;
        skymod[d[i] + 1][l[i]] /= id;
        skymod[d[i] + 1][r[i] + 1] *= id;

        id++;
    }
    for (int i = 0; i <= 2000; i++) {
        for (int j = 1; j <= 2000; j++) {
            sky[j][i] += sky[j - 1][i];
        }
    }
    for (int i = 0; i <= 2000; i++) {
        for (int j = 1; j <= 2000; j++) {
            sky[i][j] += sky[i][j - 1];
        }
    }

    for (int i = 0; i <= 2000; i++) {
        for (int j = 1; j <= 2000; j++) {
            skymod[j][i] *= skymod[j - 1][i];
        }
    }
    for (int i = 0; i <= 2000; i++) {
        for (int j = 1; j <= 2000; j++) {
            skymod[i][j] *= skymod[i][j - 1];
        }
    }

    vector<int> cnt(n, 0);
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            if (sky[i][j] == skymod[i][j].val() && sky[i][j] != 0) {
                cnt[sky[i][j] - 2]++;
            }
        }
    }

    int base = 0;
    for (int i = 0; i < 2000; i++) {
        for (int j = 0; j < 2000; j++) {
            if (sky[i][j] == 0) {
                base++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << base + cnt[i] << endl;
    }
}
