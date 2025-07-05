# include <bits/stdc++.h>
# include <atcoder/all>
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
#     int t;
#     cin >> t;
#     while (t--) {
#         int n;
#         cin >> n;
#         vector<int> a(n);
#         for (int i = 0; i < n; i++) {
#             cin >> a[i];
#         }
#         sort(all(a), [](int a, int b) { return abs(a) < abs(b); });
#         bool ans = false;
#         int hi;
#         if (a[1] % a[0] == 0) {
#             hi = a[1] / a[0];
#             bool tmp = true;
#             for (int i = 2; i < n; i++) {
#                 if (a[i] / a[i - 1] == hi) {
#                     continue;
#                 } else {
#                     tmp = false;
#                 }
#             }
#             if (tmp) {
#                 ans = true;
#             }
#         }
#         if (ans) {
#             cout << "Yes" << endl;
#         } else {
#             cout << "No" << endl;
#         }
#     }
# }

# AI翻訳を改変

import sys
from fractions import Fraction


def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = list(map(int, input().split()))
        # 絶対値でソート
        a.sort(key=abs)
        ans = True
        hi = Fraction(a[1], a[0])
        for i in range(2, n):
            if Fraction(a[i], a[i - 1]) == hi:
                continue
            else:
                ans = False
                break
        # 結果出力
        print("Yes" if ans else "No")


if __name__ == "__main__":
    main()
