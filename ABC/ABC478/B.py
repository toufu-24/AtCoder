n,v = map(int, input().split())
a = list(map(int, input().split()))

import itertools

ans = 0
for x in itertools.combinations(range(n), 3):
    cost = 0
    val = 0
    for xx in x:
        cost += xx + 1
        val += a[xx]
    if cost <= v:
        ans = max(ans, val)

print(ans)
