# #include <bits/stdc++.h>
# #include <atcoder/all>
# using namespace std;
# using namespace atcoder;

# #define all(v) v.begin(), v.end()
# #define SORT(v) sort(v.begin(), v.end())
# #define RSORT(v) sort(v.rbegin(), v.rend())
# #define REVERSE(v) reverse(v.begin(), v.end())
# #define ll int64_t
# #define ld long double

# #define int ll

# int32_t main()
# {
#     int A, M, L, R;
#     cin >> A >> M >> L >> R;
#     L -= A;
#     R -= A;
#     ll ans = R / M - (L - 1) / M;
#     cout << ans << endl;
# }

A, M, L, R = map(int, input().split())
L -= A
R -= A
ans = R // M - (L - 1) // M
print(ans)
