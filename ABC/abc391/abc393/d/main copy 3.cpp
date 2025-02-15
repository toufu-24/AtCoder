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
    string s;
    cin >> s;
    int first_one = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            first_one = i;
            break;
        }
    }
    string pre = s.substr(0, first_one);
    string suf = s.substr(first_one);
    s = suf + pre;

    int ans = 0;
    int left = 1;
    int right = n - 2;
    assert(s[0] == '0');
    assert(s[n - 1] == '0');
    for (int i = 0; i < n / 2; i++) {
        if (s[i] == '0') {
            ans += i - left;
            left++;
        }
        if (s[n - 1 - i] == '0') {
            ans += right - (n - 1 - i);
            right--;
        }
    }

    cout << ans << endl;
}
