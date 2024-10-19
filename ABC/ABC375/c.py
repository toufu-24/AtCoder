import numpy as np

n = int(input())
a = np.array([list(input().strip()) for _ in range(n)])

# 回転処理
for i in range(n // 2):
    start = i
    end = n - i - 1
    angle = (90 * (i + 1)) % 360
    for i in range(start, end):
        for _ in range(angle // 90):
            top = a[start, i]
            right = a[i, end]
            bottom = a[end, end - (i - start)]
            left = a[end - (i - start), start]

            a[start, i] = left
            a[i, end] = top
            a[end, end - (i - start)] = right
            a[end - (i - start), start] = bottom

for row in a:
    print("".join(row))
