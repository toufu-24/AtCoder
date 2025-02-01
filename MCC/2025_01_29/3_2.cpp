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
    string s = "wbwbwwbwbwbw";
    string st = s;
    for (int i = 0; i < 30; i++) {
        st += s;
    }

    for (int i = 0; i < st.size(); i++) {
        for (int j = i; j < st.size(); j++) {
            int cnt_w = 0, cnt_b = 0;
            for (int k = i; k <= j; k++) {
                if (st[k] == 'w') {
                    cnt_w++;
                } else {
                    cnt_b++;
                }
            }
            if (cnt_w == w && cnt_b == b) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}
