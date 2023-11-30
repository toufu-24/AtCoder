import bisect
import sys

input = sys.stdin.readline

N, M, K = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

sum_A = [0] * (N + 1)
for i in range(N):
    sum_A[i + 1] = sum_A[i] + A[i]

sum_B = [0] * (M + 1)
for i in range(M):
    sum_B[i + 1] = sum_B[i] + B[i]

ans = 0
for i in range(N):
    if sum_A[i + 1] > K:
        break
    idx = bisect.bisect_right(sum_B, K - sum_A[i + 1])
    ans = max(ans, i + idx)

print(ans)
