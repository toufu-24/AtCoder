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

int how_many_swap(vector<int> a) {
    int n = a.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (a[j + 1] < a[j]) {
                swap(a[j], a[j + 1]);
                ans++;
            }
        }
    }
    return ans;
}

int32_t main() {
    int h, w;
    cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> b(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> b[i][j];
        }
    }

    vector<int> h_perm(h);
    iota(all(h_perm), 0);
    vector<int> w_perm(w);
    iota(all(w_perm), 0);
    int ans = 1e18;
    do {
        do {
            vector<vector<int>> c(h, vector<int>(w));
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    c[i][j] = a[h_perm[i]][w_perm[j]];
                }
            }
            bool ok = true;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (c[i][j] != b[i][j]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ok) {
                int h_swaps = how_many_swap(h_perm);
                int w_swaps = how_many_swap(w_perm);
                ans = min(ans, h_swaps + w_swaps);
            }
        } while (next_permutation(all(w_perm)));
    } while (next_permutation(all(h_perm)));
    cout << (ans == 1e18 ? -1 : ans) << endl;
}
