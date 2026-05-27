from decimal import *

a, b = input().split()
a = int(a)
b = Decimal(b)

ans = a * b
ans //= 1
print(ans)
