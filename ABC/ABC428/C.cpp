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
    int q;
    cin >> q;
    int bad_cnt = 0;
    int remain_left = 0;
    vector<pair<char, bool>> now;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            char c;
            cin >> c;
            bool ok = true;
            if (c == '(') {
                remain_left++;
            } else {
                if (remain_left > 0) {
                    remain_left--;
                } else {
                    bad_cnt++;
                    ok = false;
                }
            }
            now.push_back({c, ok});
        } else {
            auto x = now.back();
            now.pop_back();
            if (x.first == '(') {
                remain_left--;
            } else {
                if (!x.second) {
                    bad_cnt--;
                } else {
                    remain_left++;
                }
            }
        }
        if (bad_cnt == 0 && remain_left == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
