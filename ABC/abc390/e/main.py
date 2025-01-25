n, x = map(int, input().split())
v = []
a = []
c = []
for _ in range(n):
    vi, ai, ci = map(int, input().split())
    v.append(vi)
    a.append(ai)
    c.append(ci)

ones = []
twos = []
threes = []
for i in range(n):
    if v[i] == 1:
        ones.append((v[i], a[i], c[i]))
    elif v[i] == 2:
        twos.append((v[i], a[i], c[i]))
    else:
        threes.append((v[i], a[i], c[i]))

from decimal import *

ones.sort(key=lambda x: Decimal(x[1]) / Decimal(x[2]), reverse=True)
twos.sort(key=lambda x: Decimal(x[1]) / Decimal(x[2]), reverse=True)
threes.sort(key=lambda x: Decimal(x[1]) / Decimal(x[2]), reverse=True)

arr = [ones, twos, threes]
idxes = [0, 0, 0]
sums = [0, 0, 0]
now_calories = 0
while now_calories <= x:
    min_idx = -1
    min_val = 10**9
    for i in range(3):
        if idxes[i] < len(arr[i]) and sums[i] < min_val:
            min_val = sums[i]
            min_idx = i
    if min_idx == -1:
        break
    if now_calories + arr[min_idx][idxes[min_idx]][2] > x:
        break
    sums[min_idx] += arr[min_idx][idxes[min_idx]][1]
    now_calories += arr[min_idx][idxes[min_idx]][2]
    idxes[min_idx] += 1

print(min(sums))
