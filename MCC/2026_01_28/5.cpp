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

// https://qiita.com/drken/items/a14e9af0ca2d857dad23#3-1-%E7%B4%84%E6%95%B0%E5%88%97%E6%8C%99
vector<long long> enum_divisors(long long N) {
    vector<long long> res;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            res.push_back(i);
            // 重複しないならば i の相方である N/i も push
            if (N / i != i) res.push_back(N / i);
        }
    }
    // 小さい順に並び替える
    sort(res.begin(), res.end());
    return res;
}

int32_t main() {
    int n;
    cin >> n;
    auto res = enum_divisors(n);
    int ans = 1e18;
    for (auto x : res) {
        string s_x = to_string(x);
        string s_y = to_string(n / x);
        ans = min<int>(ans, max(s_x.size(), s_y.size()));
    }
    cout << ans << endl;
}
