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
    int w, b;
    cin >> w >> b;
    string st = "wbwbwwbwbwbw";
    // for (int i = 0; i < 30; i++) {
    //     st += st;
    // }

    int one_w = 0, one_b = 0;
    for (int i = 0; i < st.size(); i++) {
        if (st[i] == 'w') {
            one_w++;
        } else {
            one_b++;
        }
    }

    int w_cnt = w / one_w;
    int b_cnt = b / one_b;
    cerr << w_cnt << " " << b_cnt << endl;
    int cnt = min(w_cnt, b_cnt);
    w -= cnt * one_w;
    b -= cnt * one_b;
    cerr << w << " " << b << endl;
    for (int left = 0; left < st.size(); left++) {
        for (int right = 0; right < st.size(); right++) {
            int w_cnt = 0, b_cnt = 0;
            for (int i = left; i < st.size(); i++) {
                if (st[i] == 'w') {
                    w_cnt++;
                } else {
                    b_cnt++;
                }
            }
            for (int i = 0; i <= right; i++) {
                if (st[i] == 'w') {
                    w_cnt++;
                } else {
                    b_cnt++;
                }
            }
            if (w_cnt == w && b_cnt == b) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}
