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
    vector<int> prev_black(n, -1), prev_white(n, 0);
    vector<int> cnt(n, 0);
    int ti = 0;
    vector<int> ccnt, bcnt;
    ccnt.push_back(0);
    bcnt.push_back(0);
    int ans = 0;
    while (q--) {
        ti++;

        int op;
        cin >> op;
        if (op == 1) {
            int r;
            cin >> r;
            r--;
            int pre = prev_black[r];
            if (pre == -1) {
                ans += n;
            } else {
                ans += ccnt.back() - ccnt[pre];
            }
            prev_black[r] = ti;
            ccnt.push_back(ccnt.back());
        } else {
            int c;
            cin >> c;
            ccnt.push_back(ccnt.back() + 1);
        }
        cout << ans << endl;
    }
}
