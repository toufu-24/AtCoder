import numpy as np

N = int(input())
ans = np.full((N, N), -1)
for i in range(N):
    ans[0, i] = i + 1
ans = ans.T

i = N
while i > 0:
    for j in range(1, N + 1):
        ans[i - 1, j - 1] = i * j
    ans = ans.T

for i in range(N):
    for j in range(N):
        print(ans[i, j], end=" ")
    print()
