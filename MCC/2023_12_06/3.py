K = int(input())
num = "7"
for i in range(K):
    if int(num) % K == 0:
        print(i + 1)
        exit()
    num += "7"
print(-1)