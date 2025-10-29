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

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        string left = s.substr(0, s.size() / 2);
        string right = s.substr(s.size() / 2);
        REVERSE(right);
        int ans1 = calc(left) + calc(right);
        int ans2 = calc(flip(left)) + calc(flip(right));

        string left2 = s.substr(0, s.size() / 2 + 1);
        string right2 = s.substr(s.size() / 2 + 1);
        REVERSE(right2);
        int ans3 = calc(left2) + calc(right2);
        int ans4 = calc(flip(left2)) + calc(flip(right2));
        cout << min({ans1, ans2, ans3, ans4}) << endl;
    }
}
