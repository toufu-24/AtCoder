import math

S = input()
N = len(S)
ans = math.comb(N, 2)
count = {}
for s in S:
    if s in count:
        count[s] += 1
    else:
        count[s] = 1

flag = False
for k, v in count.items():
    if v > 1:
        flag = True
        ans -= math.comb(v, 2)
if flag:
    ans += 1

print(ans)
