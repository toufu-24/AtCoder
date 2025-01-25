N = int(int(input()))
A = list(map(int, input().split()))

from decimal import *

div = Decimal(A[1]) / Decimal(A[0])

for i in range(2, N):
    if Decimal(A[i]) / Decimal(A[i - 1]) != div:
        print("No")
        exit()

print("Yes")
