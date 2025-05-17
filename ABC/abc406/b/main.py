# -*- coding: utf-8 -*-
# -------------------- Original C++ code (DO NOT EDIT) --------------------
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
#     int n, k;
#     cin >> n >> k;
#     vector<int> a(n);
#     for (int i = 0; i < n; i++) {
#         cin >> a[i];
#     }
#     int ans = 1;
#     for (int i = 0; i < n; i++) {
#         ans *= a[i];
#         string tmp = to_string(ans);
#         if (tmp.size() > k) {
#             ans = 1;
#         }
#     }
#     string ans_s = to_string(ans);
#     if (ans_s.size() > k) {
#         cout << 1 << endl;
#     } else {
#         cout << ans_s << endl;
#     }
# }
# -------------------------------------------------------------------------

import sys


def main() -> None:
    # 1 行に n, k が揃っていないケースにも対応
    nk = sys.stdin.readline().split()
    while len(nk) < 2:
        nk += sys.stdin.readline().split()
    n, k = map(int, nk)

    # n 個読み切るまで整数を取得
    a: list[int] = []
    while len(a) < n:
        a += list(map(int, sys.stdin.readline().split()))

    ans = 1
    for x in a:
        ans *= x
        # 桁数が k を超えたらリセット
        if len(str(ans)) > k:
            ans = 1

    # 最終出力
    print(1 if len(str(ans)) > k else ans)


if __name__ == "__main__":
    main()
