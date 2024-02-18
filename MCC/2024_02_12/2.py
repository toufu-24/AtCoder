N = int(input())
A = list(map(int, input().split()))
ans = []
dp = [[0, 0] for _ in range(N + 1)]
dp[0][0] = 1
dp[0][1] = 0
for i in range(N):
    dp[i + 1][0] = max(dp[i][0], dp[i][1] - A[i])
    dp[i + 1][1] = max(dp[i][1], dp[i][0] + A[i])

# 動的計画法の復元
now = dp[N][0]
idx = 0
for i in range(N - 1, -1, -1):
    if now == dp[i][1] - A[i] and idx == 0:
        ans.append(1)
        now = dp[i][1]
        idx = 1
    elif now == dp[i][0] + A[i] and idx == 1:
        ans.append(1)
        now = dp[i][0]
        idx = 0
    else:
        ans.append(0)
        now = dp[i][idx]

ans = ans[::-1]
print(*ans)