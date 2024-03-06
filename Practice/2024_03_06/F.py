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
#     int X, A, D, N;
#     cin >> X >> A >> D >> N;
#     if (D < 0)
#     {
#         A = A + (N - 1) * D;
#         D = -D;
#     }

#     // 項をにぶたん
#     int left = 0, right = N;
#     while (right - left > 1)
#     {
#         int mid = (left + right) / 2;
#         if (A + mid * D < X)
#         {
#             left = mid;
#         }
#         else
#         {
#             right = mid;
#         }
#     }

#     cout << abs(X - (A + left * D)) << endl;
# }

X, A, D, N = map(int, input().split())
if D < 0:
    A = A + (N - 1) * D
    D = -D

left = 0
right = N
while right - left > 1:
    mid = (left + right) // 2
    if A + mid * D < X:
        left = mid
    else:
        right = mid

print(abs(X - (A + left * D)))
