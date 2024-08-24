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
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        // 3 1 1の周期で減らせる
        int amari = h[i] % 5; // 余り
        t += (h[i] / 5) * 3; // 何ステップ
        h[i] = amari;
        while (h[i] > 0) {
            t++;
            if (t % 3 == 0) {
                h[i] -= 3;
            } else {
                h[i] -= 1;
            }
        }
    }
    cout << t;
}
