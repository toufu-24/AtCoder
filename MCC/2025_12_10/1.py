h,w = map(int, input().split())
import numpy as np
a = []
for i in range(h):
    tmp = list(map(int, input().split()))
    a.append(tmp)
a_np = np.array(a)
b = a_np.T
for i in range(w):
    for j in range(h):
        print(b[i][j], end=' ')
    print()