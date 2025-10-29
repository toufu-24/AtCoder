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

int calc(string s) {
    int n = s.size();
    // 1を左側に寄せる
    int ret = 0;
    int leftest_one = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') {
            leftest_one = i;
            break;
        }
    }
    if (leftest_one == -1) {
        return 0;
    }
    int one_cnt = 0;
    for (int i = 0; i < leftest_one; i++) {
        if (s[i] == '1') {
            one_cnt++;
        }
    }
    return leftest_one + (leftest_one + 1) - one_cnt;
}

string flip(string s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = (s[i] == '0' ? '1' : '0');
    }
    return s;
}

int op(int a, int b) {
    return a + b;
}

int e() {
    return 0;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        int ans;
        {
            segtree<int, op, e> seg(n);
            vector<int> ones;
            for (int i = 0; i < n; i++) {
                seg.set(i, s[i] == '0');
                if (s[i] == '1') {
                    ones.push_back(i);
                }
            }
            if (ones.size() == 0) {
                cout << 0 << endl;
                continue;
            } else if (ones.size() == 1) {
                int ans = min(calc(s), calc(flip(s)));
                REVERSE(s);
                int ans2 = min(calc(s), calc(flip(s)));
                cout << min(ans, ans2) << endl;
                continue;
            }

            int min_zero = 1e9;
            pair<int, int> min_pair;
            for (int i = 0; i < ones.size() - 1; i++) {
                int left = ones[i], right = ones[i + 1];
                if (seg.prod(0, left) + seg.prod(right, n) < min_zero) {
                    min_pair = {left, right};
                    min_zero = seg.prod(0, left) + seg.prod(right, n);
                }
            }

            string left_s = s.substr(0, min_pair.first + 1);
            string right_s = s.substr(min_pair.second);
            REVERSE(right_s);
            ans = calc(left_s) + calc(right_s);
        }
        s = flip(s);
        {
            segtree<int, op, e> seg(n);
            vector<int> ones;
            for (int i = 0; i < n; i++) {
                seg.set(i, s[i] == '0');
                if (s[i] == '1') {
                    ones.push_back(i);
                }
            }
            if (ones.size() == 0) {
                cout << 0 << endl;
                continue;
            } else if (ones.size() == 1) {
                int ans = min(calc(s), calc(flip(s)));
                REVERSE(s);
                int ans2 = min(calc(s), calc(flip(s)));
                cout << min(ans, ans2) << endl;
                continue;
            }

            int min_zero = 1e9;
            pair<int, int> min_pair;
            for (int i = 0; i < ones.size() - 1; i++) {
                int left = ones[i], right = ones[i + 1];
                if (seg.prod(0, left) + seg.prod(right, n) < min_zero) {
                    min_pair = {left, right};
                    min_zero = seg.prod(0, left) + seg.prod(right, n);
                }
            }

            string left_s = s.substr(0, min_pair.first + 1);
            string right_s = s.substr(min_pair.second);
            REVERSE(right_s);
            ans = min(ans, calc(left_s) + calc(right_s));
        }
        cout << ans << endl;
    }
}