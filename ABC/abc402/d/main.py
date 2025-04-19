# 以下はオリジナルのC++コードです：
#
# #include <bits/stdc++.h>
# #include <atcoder/all>
# using namespace std;
# using namespace atcoder;
#
# #define all(v) v.begin(), v.end()
# #define SORT(v) sort(v.begin(), v.end())
# #define RSORT(v) sort(v.rbegin(), v.rend())
# #define REVERSE(v) reverse(v.begin(), v.end())
# #define ll long
# #define ld long double
#
# #define int ll
#
# int32_t main() {
#     int n, m;
#     cin >> n >> m;
#     vector<int> a(m), b(m);
#     for (int i = 0; i < m; i++) {
#         cin >> a[i] >> b[i];
#     }
#     set<pair<int, int>> lines;
#     for (int i = 0; i < m; i++) {
#         if (a[i] > b[i]) {
#             swap(a[i], b[i]);
#         }
#         lines.insert({a[i], b[i]});
#     }
#
#     int ans = m * (m - 1) / 2;
#     // 平行ならまじわらない
#     // x1:y1 = x2:y2
#     // x1 * y2 = x2 * y1
#     // x1/y1 = x2/y2
#     for (auto [x, y] : lines) {
#     }
# }


n, m = map(int, input().split())
a = [0] * m
b = [0] * m
for i in range(m):
    a[i], b[i] = map(int, input().split())

from fractions import Fraction

lines = []
for i in range(m):
    if a[i] > b[i]:
        a[i], b[i] = b[i], a[i]
    lines.append(Fraction(a[i], b[i]))

lines = sorted(lines)
ans = m * (m - 1) // 2

# 平行ならまじわらない
# x1:y1 = x2:y2
# x1 * y2 = x2 * y1
# x1/y1 = x2/y2
same_cnt = 0
for i in range(m):
    # 一致するものを削除
    if i > 0 and lines[i] == lines[i - 1]:
        same_cnt += 1
    else:
        ans -= (same_cnt) * (same_cnt - 1) // 2
        same_cnt = 0

ans -= (same_cnt) * (same_cnt - 1) // 2
print(ans)
