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
    string s;
    cin >> s;
    deque<char> dq;
    for (auto x : s) {
        dq.push_back(x);
    }
    int q;
    cin >> q;
    bool rev = false;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            rev = !rev;
        } else {
            int f;
            char c;
            cin >> f >> c;
            if (f == 1) {
                if (!rev) {
                    dq.push_front(c);
                } else {
                    dq.push_back(c);
                }
            } else {
                if (rev) {
                    dq.push_front(c);
                } else {
                    dq.push_back(c);
                }
            }
        }
    }
    string ans;
    for (auto itr = dq.begin(); itr != dq.end(); itr++) {
        ans += *itr;
    }
    if(rev){
        REVERSE(ans);
    }
    cout << ans << endl;
}