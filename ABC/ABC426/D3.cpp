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
        int ans = 1e18;
        {
            segtree<int, op, e> seg(n);
            vector<int> ones;
            for (int i = 0; i < n; i++) {
                seg.set(i, s[i] == '1');
                if (s[i] == '1') {
                    ones.push_back(i);
                }
            }
            if (ones.size() == 0) {
                ans = 0;
            } else if (ones.size() == 1) {
                int ans1 = min(calc(s), calc(flip(s)));
                REVERSE(s);
                int ans2 = min(calc(s), calc(flip(s)));
                ans = min({ans, ans1, ans2});
            } else {
                for (int i = 0; i < ones.size() - 1; i++) {
                    int left = ones[i], right = ones[i + 1];
                    int left_cos = left + (left + 1) - seg.prod(0, left + 1);
                    int right_cos = (n - right) + ((n - right) + 1) - seg.prod(right, n);
                    ans = min(left_cos + right_cos, ans);
                }
            }
            ans = min(ans, calc(s));
            REVERSE(s);
            ans = min(ans, calc(s));
            REVERSE(s);
        }

        s = flip(s);
        {
            segtree<int, op, e> seg(n);
            vector<int> ones;
            for (int i = 0; i < n; i++) {
                seg.set(i, s[i] == '1');
                if (s[i] == '1') {
                    ones.push_back(i);
                }
            }
            if (ones.size() == 0) {
                ans = 0;
            } else if (ones.size() == 1) {
                int ans1 = min(calc(s), calc(flip(s)));
                REVERSE(s);
                int ans2 = min(calc(s), calc(flip(s)));
                ans = min({ans, ans1, ans2});
            } else {
                for (int i = 0; i < ones.size() - 1; i++) {
                    int left = ones[i], right = ones[i + 1];
                    int left_cos = left + (left + 1) - seg.prod(0, left + 1);
                    int right_cos = (n - right) + ((n - right) + 1) - seg.prod(right, n);
                    ans = min(left_cos + right_cos, ans);
                }
            }
            ans = min(ans, calc(s));
            REVERSE(s);
            ans = min(ans, calc(s));
            REVERSE(s);
        }
        cout << ans << endl;
    }
}