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

#define pow2(x) ((x) * (x))

int32_t main() {
    int n;
    cin >> n;
    int s, t;
    cin >> s >> t;
    vector<vector<int>> ABCD(n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> ABCD[i][j];
        }
    }

    ld ans = 1e18;
    vector<int> perm(n);
    iota(all(perm), 0);
    do {
        for (int flip = 0; flip < (1 << n); flip++) {
            ld tmp_ans = 0;
            pair<int, int> now = {0, 0};
            for (int i = 0; i < n; i++) {
                int a = ABCD[perm[i]][0];
                int b = ABCD[perm[i]][1];
                int c = ABCD[perm[i]][2];
                int d = ABCD[perm[i]][3];

                if (flip & (1 << i)) {
                    swap(a, c);
                    swap(b, d);
                }

                // now -> {a, b}
                ld ab_dist = sqrtl(pow2(a - now.first) + pow2(b - now.second));
                ld ab_time = ab_dist / s;
                // {a, b} -> {c, d}
                ld cd_dist = sqrtl(pow2(c - a) + pow2(d - b));
                ld cd_time = cd_dist / t;
                tmp_ans += ab_time + cd_time;
                now = {c, d};
            }
            ans = min(ans, tmp_ans);
        }
    } while (next_permutation(all(perm)));
    cout << fixed << setprecision(10) << ans << endl;
}
