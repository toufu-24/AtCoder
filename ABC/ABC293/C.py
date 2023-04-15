import sys
from collections import defaultdict

input = sys.stdin.readline

H, W = map(int, input().split())
matrix = [[0] * (W + 1) for _ in range(H + 1)]
for i in range(1, H + 1):
    matrix[i][1 : W + 1] = list(map(int, input().split()))

dp_set = [[[] for _ in range(W + 1)] for _ in range(H + 1)]
dp_set[1][1].append(set([matrix[1][1]]))
dp = [[[] for _ in range(W + 1)] for _ in range(H + 1)]
dp[1][1].append(1)

for i in range(1, H + 1):
    for j in range(1, W + 1):
        for k in range(len(dp_set[i - 1][j])):
            if matrix[i][j] not in dp_set[i - 1][j][k]:
                tmp = set(dp_set[i - 1][j][k])
                tmp.add(matrix[i][j])
                dp_set[i][j].append(tmp)
                dp[i][j].append(dp[i - 1][j][k])

        for k in range(len(dp_set[i][j - 1])):
            if matrix[i][j] not in dp_set[i][j - 1][k]:
                tmp = set(dp_set[i][j - 1][k])
                tmp.add(matrix[i][j])
                dp_set[i][j].append(tmp)
                dp[i][j].append(dp[i][j - 1][k])

ans = sum(dp[H][W])
print(ans)
