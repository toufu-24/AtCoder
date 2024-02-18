import bisect

N, P, Q, R = map(int, input().split())
A = list(map(int, input().split()))
sum = [0] * (N + 1)
for i in range(1, N):
    sum[i] = sum[i - 1] + A[i - 1]

for x in range(N):
    # P
    y = bisect.bisect_left(sum, P + sum[x])
    if y == N + 1 or sum[y] - sum[x] != P:
        continue
    # Q
    z = bisect.bisect_left(sum, Q + sum[y])
    if z == N + 1 or sum[z] - sum[y] != Q:
        continue
    # R
    w = bisect.bisect_left(sum, R + sum[z])
    if w == N + 1 or sum[w] - sum[z] != R:
        continue
    print("Yes")
    exit()
print("No")
