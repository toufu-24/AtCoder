# #include <bits/stdc++.h>
# #include <atcoder/all>
# using namespace std;
# using namespace atcoder;

# #define all(v) v.begin(), v.end()
# #define sort(v) sort(v.begin(), v.end())
# #define reverse(v) reverse(v.begin(), v.end())
# #define ll int64_t

# int main()
# {
#     int W, H;
#     cin >> W >> H;
#     int N;
#     cin >> N;
#     vector<vector<int>> grid(H + 1, vector<int>(W + 1, 0));
#     for (int i = 0; i < N; i++)
#     {
#         int x, y;
#         cin >> x >> y;
#         grid[y][x] = 1;
#     }
#     // 2次元累積和
#     vector<vector<int>> sum(H + 1, vector<int>(W + 1, 0));
#     for (int i = 1; i <= H; i++)
#     {
#         for (int j = 1; j <= W; j++)
#         {
#             sum[i][j] = sum[i][j - 1] + grid[i][j];
#         }
#     }
#     for (int j = 1; j <= W; j++)
#     {
#         for (int i = 1; i <= H; i++)
#         {
#             sum[i][j] = sum[i - 1][j] + sum[i][j];
#         }
#     }

#     int A;
#     cin >> A;
#     vector<int> x_cut(A);
#     for (int i = 0; i < A; i++)
#     {
#         cin >> x_cut[i];
#     }
#     int B;
#     cin >> B;
#     vector<int> y_cut(B);
#     for (int i = 0; i < B; i++)
#     {
#         cin >> y_cut[i];
#     }

#     int min_ans = 1e6;
#     int max_ans = 0;
#     int start_x = 1;
#     int start_y = 1;
#     for (int i = 0; i < A; i++)
#     {
#         for (int j = 0; j < B; j++)
#         {
#             int end_x = x_cut[i];
#             int end_y = y_cut[j];
#             int area = sum[end_y][end_x] - sum[start_y - 1][end_x] - sum[end_y][start_x - 1] + sum[start_y - 1][start_x - 1];
#             min_ans = min(min_ans, area);
#             max_ans = max(max_ans, area);
#             start_x = end_x + 1;
#         }
#     }

#     cout << min_ans << " " << max_ans << endl;
# }

#上記のC++コードをPythonに書き換えたもの

import numpy as np

H, W = map(int, input().split())
N = int(input())
grid = np.zeros((H + 1, W + 1), dtype=int)
for i in range(N):
    x, y = map(int, input().split())
    grid[y][x] = 1

sum = np.zeros((H + 1, W + 1), dtype=int)
for i in range(1, H + 1):
    for j in range(1, W + 1):
        sum[i][j] = sum[i][j - 1] + grid[i][j]

for j in range(1, W + 1):
    for i in range(1, H + 1):
        sum[i][j] = sum[i - 1][j] + sum[i][j]

A = int(input())
x_cut = list(map(int, input().split()))
B = int(input())
y_cut = list(map(int, input().split()))

min_ans = 1e6
max_ans = 0
start_x = 1
start_y = 1
for i in range(A):
    for j in range(B):
        end_x = x_cut[i]
        end_y = y_cut[j]
        area = sum[end_y][end_x] - sum[start_y - 1][end_x] - sum[end_y][start_x - 1] + sum[start_y - 1][start_x - 1]
        min_ans = min(min_ans, area)
        max_ans = max(max_ans, area)
        start_x = end_x + 1

print(min_ans, max_ans)