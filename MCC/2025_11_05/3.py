n = int(input())
ans = []
while n != 0:
    n -= 1
    ans.append(n % 26)
    n //= 26
ans.reverse()
for i, c in enumerate(ans):
    print(chr(c + 97), end="")
