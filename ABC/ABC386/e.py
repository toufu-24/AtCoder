from itertools import combinations

n, k = map(int, input().split())
a = list(map(int, input().split()))


def xor(v):
    res = 0
    for i in v:
        res ^= i
    return res


ans = 0
all_xor = xor(a)

flag = False
if n / 2 <= k:
    k = n - k
    flag = True
for v in combinations(a, k):
    if flag:
        ans = max(ans, all_xor ^ xor(v))
    else:
        ans = max(ans, xor(v))
print(ans)
