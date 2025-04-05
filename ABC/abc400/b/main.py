N, M = map(int, input().split())

x = 0
for i in range(M + 1):
    x += N**i
    if x > 10**9:
        print("inf")
        break
else:
    print(x)
