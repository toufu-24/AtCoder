import numpy as np

n, k = map(int, input().split())

x = list(map(int, input().split()))
x = [i - 1 for i in x] 

a = list(map(int, input().split()))

M = np.zeros((n, n), dtype=int)
for i in range(n):
    M[i][x[i]] = 1

Mk = np.eye(len(M), dtype=int)
while k > 0:
    if k % 2 == 1:
        Mk = np.dot(Mk, M)
    M = np.dot(M, M)
    k //= 2

ans = np.dot(Mk, a)

print(' '.join(map(str, ans)))
