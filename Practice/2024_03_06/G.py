import math

A, B = map(int, input().split())


def f(B_cnt):
    return B * B_cnt + A / math.sqrt(B_cnt + 1)


low, high = 0, A + 1
while high - low > 2:
    c1 = (low * 2 + high) // 3
    c2 = (low + high * 2) // 3
    if f(c1) > f(c2):
        low = c1
    else:
        high = c2

ans = float("inf")
for i in range(low, high + 1):
    ans = min(ans, f(i))

print("{:.10f}".format(ans))
