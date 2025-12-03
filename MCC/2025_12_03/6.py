s = input()
n = len(s)
if n == 1:
    print(s)
    exit(0)
ans = 0
for mask in range(2 ** (n - 1)):
    bi = bin(mask)[2:]
    lbi = len(bi)
    tmp = ''
    for i in range(n-1 - lbi):
        bi = "0" + bi
    for i, c in enumerate(bi):
        tmp = tmp + s[i]
        if c == '1':
            tmp = tmp + '+'
    tmp = tmp + s[-1]
    # print(tmp)
    ans += eval(tmp)
print(ans)
