ans = 0
v = list(map(int, input().split()))
S = ""
for i in range(64):
    S += str(v[i])
for i in range(len(S)):
    if S[i] == "1":
        tmp = 1
        for j in range(i):
            tmp *= 2
        ans += tmp
print(ans)