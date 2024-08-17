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

using mint998 = modint998244353;
using mint107 = modint1000000007;

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[i]++;
    }

    vector<mint998> a_mul(n + 1, 1), b_mul(n + 1, 1);
    vector<mint998> a_sum(n + 1, 0), b_sum(n + 1, 0);
    vector<mint107> a_mul2(n + 1, 1), b_mul2(n + 1, 1);
    vector<mint107> a_sum2(n + 1, 0), b_sum2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        a_mul[i + 1] = a_mul[i] * a[i];
        b_mul[i + 1] = b_mul[i] * b[i];
        a_mul2[i + 1] = a_mul2[i] * a[i];
        b_mul2[i + 1] = b_mul2[i] * b[i];
        a_sum[i + 1] = a_sum[i] + a[i];
        b_sum[i + 1] = b_sum[i] + b[i];
        a_sum2[i + 1] = a_sum2[i] + a[i];
        b_sum2[i + 1] = b_sum2[i] + b[i];
    }

    while (q--) {
        int al, ar, bl, br;
        cin >> al >> ar >> bl >> br;
        al--, ar--, bl--, br--;
        if (ar - al != br - bl) {
            cout << "No" << endl;
            continue;
        }
        mint998 a_tmp = a_mul[ar + 1] / a_mul[al], b_tmp = b_mul[br + 1] / b_mul[bl];
        mint107 a_tmp2 = a_mul2[ar + 1] / a_mul2[al], b_tmp2 = b_mul2[br + 1] / b_mul2[bl];
        mint998 a_tmp3 = a_sum[ar + 1] - a_sum[al], b_tmp3 = b_sum[br + 1] - b_sum[bl];
        mint107 a_tmp4 = a_sum2[ar + 1] - a_sum2[al], b_tmp4 = b_sum2[br + 1] - b_sum2[bl];
        if (a_tmp == b_tmp && a_tmp2 == b_tmp2 && a_tmp3 == b_tmp3 && a_tmp4 == b_tmp4) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
