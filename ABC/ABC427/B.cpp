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
    int ans = 0;
    map<int, int> f_memo, i_memo;
    auto f = [&](auto f, int a) -> int {
        if (f_memo.contains(a)) {
            return f_memo[a];
        }
        string s = to_string(a);
        int sum = 0;
        for (int j = 0; j < s.size(); j++) {
            sum += s[j] - '0';
        }
        return f_memo[a] = sum;
    };
    auto calc_i = [&](auto calc_i, int i) -> int {
        if (i == 0) {
            return 1;
        }
        if (i_memo.contains(i)) {
            return i_memo[i];
        }
        int ret = 0;
        for (int j = 0; j < i; j++) {
            ret += f(f, calc_i(calc_i, j));
        }
        return i_memo[i] = ret;
    };
    cout << calc_i(calc_i, n) << endl;
}
