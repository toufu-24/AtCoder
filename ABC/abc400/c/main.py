import math

n = int(input())

ans = 0
for a in range(1, 64):
    tmp = 1 << a
    # tmp * b^2 <= nである最大のb
    # b^2 <= n / tmp
    b = int(math.sqrt(n / tmp))
    ans += b

    # 包除原理
    dec_tmp = 0
    for i in range(1, a):
        ans -= b // (1 << i) - dec_tmp
        dec_tmp += b // (1 << i) - dec_tmp
    ans -= dec_tmp
print(ans)
