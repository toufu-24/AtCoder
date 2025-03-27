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

using mint = modint998244353;

int32_t main() {
    int n;
    cin >> n;
    mint ans = 0;
    string str_n = to_string(n);
    for (int i = 0; i < str_n.size(); i++) {
        int d = str_n[i] - '0';
        mint x = mint(10).pow(i);
        mint y = mint(10).pow(str_n.size() - i - 1);
        ans += x * y * d;
    }
    cout << ans.val() << endl;
}
