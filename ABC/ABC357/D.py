# #include <bits/stdc++.h>
# #include <atcoder/all>
# using namespace std;
# using namespace atcoder;

# #define all(v) v.begin(), v.end()
# #define SORT(v) sort(v.begin(), v.end())
# #define RSORT(v) sort(v.rbegin(), v.rend())
# #define REVERSE(v) reverse(v.begin(), v.end())
# #define ll long
# #define ld long double

# #define int ll

# using mint = modint998244353;

# int32_t main()
# {
#     int N;
#     cin >> N;
#     mint ans = 1;
#     int d = to_string(N).size();
#     ans = N * (mint(10).pow(d * N) - 1) / (mint(10).pow(d) - 1);
#     cout << ans.val() << endl;
# }

N = int(input())
ans = 1
d = len(str(N))
ans = N;
ans *= pow(10, d * N, 998244353) - 1
ans *= pow(pow(10, d, 998244353) - 1, -1, 998244353)
ans %= 998244353
print(ans)
