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
    int n, q;
    cin >> n >> q;
    modint::set_mod(n);
    modint l = 0, r = 1;
    int ans = 0;
    while (q--) {
        char h;
        int t;
        cin >> h >> t;
        t--;
        switch (h) {
        case 'L': {
            // lをtに持ってく
            bool colision = false;
            // まず右回り
            auto tmp = l;
            int left_cnt = 0;
            while (tmp.val() != t) {
                tmp++;
                left_cnt++;
                if (tmp == r) {
                    colision = true;
                    break;
                }
            }
            int right_cnt = 0;
            if (colision) {
                tmp = l;
                while (tmp.val() != t) {
                    tmp--;
                    right_cnt++;
                    if (tmp == r) {
                        assert(false);
                    }
                }
            }
            ans += colision ? right_cnt : left_cnt;
            l = t;
            break;
        }
        case 'R': {
            // rをtに持ってく
            bool colision = false;
            // まず左回り
            auto tmp = r;
            int right_cnt = 0;
            while (tmp.val() != t) {
                tmp--;
                right_cnt++;
                if (tmp == l) {
                    colision = true;
                    break;
                }
            }
            int left_cnt = 0;
            if (colision) {
                tmp = r;
                while (tmp.val() != t) {
                    tmp++;
                    left_cnt++;
                    if (tmp == l) {
                        assert(false);
                    }
                }
            }
            ans += colision ? left_cnt : right_cnt;
            r = t;
            break;
        }
        }
    }
    cout << ans << endl;
}