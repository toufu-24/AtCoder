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
    int n;
    cin >> n;
    vector<int> l(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    // +0.5して考えよう
    int ansans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<bool> positive(n, false);
        for (int i = 0; i < n; i++) {
            if ((1 << i) & mask) {
                positive[i] = true;
            }
        }

        int ans = 0;
        int now = 1;
        for (int i = 0; i < n; i++) {
            bool ini_pos = (now >= 1);
            if (positive[i]) {
                now += l[i];
            } else {
                now -= l[i];
            }

            bool pos_pos = (now >= 1);
            if(ini_pos != pos_pos){
                ans++;
            }
        }
        ansans = max(ansans, ans);
    }

    // for (int i = 0; i < n; i++) {
    //     if (now <= 0) {
    //         now += l[i];
    //         if (now >= 1) {
    //             ans++;
    //         }
    //     } else {
    //         now -= l[i];
    //         if(now <= 0 ){
    //             ans++;
    //         }
    //     }
    // }
    cout << ansans << endl;
}
