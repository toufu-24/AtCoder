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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = b[i] - a[i];
    }

    vector<bool> flip(n, false);
    for (int j = 0; j < k; j++) {
        int best_start = 0, best_end = 0;
        int start = 0;
        int max_score = -1e18;
        int score = 0;
        for (int i = 0; i < n; i++) {
            if (score + c[i] < c[i]) {
                score = c[i];
                start = i;
            } else {
                score += c[i];
            }

            if (max_score <= -1e18 || score > max_score) {
                max_score = score;
                best_start = start;
                best_end = i;
            }
        }

        if (max_score <= 0) {
            break;
        }

        for (int i = best_start; i <= best_end; i++) {
            flip[i] = !flip[i];
            if (flip[i]) {
                c[i] = a[i] - b[i];
            } else {
                c[i] = b[i] - a[i];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (flip[i]) {
            ans += b[i];
        } else {
            ans += a[i];
        }
    }
    cout << ans << endl;
}
