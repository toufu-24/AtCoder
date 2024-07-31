import numpy as np
N = int(input())
A = np.zeros((N, N), dtype=int)
for i in range(N):
    st = input()
    for j in range(N):
        A[i][j] = int(st[j])
# 転置
B = A.T
for i in range(N):
    for j in range(N):
        if j == 0 or j == N-1 or i == 0 or i == N-1:
            print(B[i][j], end='')
        else:
            print(A[i][j], end='')
    print()
