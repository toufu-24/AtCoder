# The following is the original code translated from C++ to Python.
# Original C++ code:
# ```
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
#     int h, w, X;
#     cin >> h >> w >> X;
#     int p, q;
#     cin >> p >> q;
#     p--, q--;
#     vector<vector<int>> s(h, vector<int>(w));
#     for (int i = 0; i < h; i++) {
#         for (int j = 0; j < w; j++) {
#             cin >> s[i][j];
#         }
#     }
# 
#     priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
#     pq.push({s[p][q], {p, q}});
#     vector<vector<bool>> used(h, vector<bool>(w, false));
#     int dx[] = {1, 0, -1, 0};
#     int dy[] = {0, 1, 0, -1};
#     int now = 0;
#     bool first = true;
#     while (!pq.empty()) {
#         auto [val, pos] = pq.top();
#         pq.pop();
#         auto [x, y] = pos;
#         if (used[x][y]) {
#             continue;
#         }
#         if (s[x][y] * X < now || first) {
#             used[x][y] = true;
#             now += s[x][y];
#             first = false;
#         } else {
#             continue;
#         }
#         for (int d = 0; d < 4; d++) {
#             int nx = x + dx[d];
#             int ny = y + dy[d];
#             if (nx < 0 || h <= nx || ny < 0 || w <= ny) {
#                 continue;
#             }
#             if (used[nx][ny]) {
#                 continue;
#             }
#             pq.push({s[nx][ny], {nx, ny}});
#         }
#     }
#     cout << now << endl;
# }
# ```

import heapq

def main():
    h, w, X = map(int, input().split())
    p, q = map(int, input().split())
    p -= 1
    q -= 1

    s = [list(map(int, input().split())) for _ in range(h)]

    # Priority queue implemented using heapq
    pq = []
    heapq.heappush(pq, (s[p][q], (p, q)))
    used = [[False] * w for _ in range(h)]
    dx = [1, 0, -1, 0]
    dy = [0, 1, 0, -1]

    now = 0
    first = True

    while pq:
        val, (x, y) = heapq.heappop(pq)

        if used[x][y]:
            continue

        if s[x][y] * X < now or first:
            used[x][y] = True
            now += s[x][y]
            first = False
        else:
            continue

        for d in range(4):
            nx = x + dx[d]
            ny = y + dy[d]

            if nx < 0 or nx >= h or ny < 0 or ny >= w:
                continue

            if used[nx][ny]:
                continue

            heapq.heappush(pq, (s[nx][ny], (nx, ny)))

    print(now)

if __name__ == "__main__":
    main()
