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

// https://github.com/doocs/leetcode/blob/main/solution/0200-0299/0214.Shortest%20Palindrome/README.md
typedef unsigned long long ull;

class Solution {
  public:
    string shortestPalindrome(string s) {
        int base = 131;
        ull mul = 1;
        ull prefix = 0;
        ull suffix = 0;
        int idx = 0, n = s.size();
        for (int i = 0; i < n; ++i) {
            int t = s[i] - 'a' + 1;
            prefix = prefix * base + t;
            suffix = suffix + mul * t;
            mul *= base;
            if (prefix == suffix)
                idx = i + 1;
        }
        if (idx == n)
            return s;
        string x = s.substr(idx, n - idx);
        reverse(x.begin(), x.end());
        return x + s;
    }
};

int32_t main() {
    string s;
    cin >> s;
    REVERSE(s);
    Solution solution;
    auto ans = solution.shortestPalindrome(s);
    REVERSE(ans);
    cout << ans << endl;
}
