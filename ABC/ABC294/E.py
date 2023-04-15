import sys
input = sys.stdin.readline

L, N1, N2 = map(int, input().split())
v1, l1 = [], []
for i in range(N1):
    v, l = map(int, input().split())
    v1.append(v)
    l1.append(l)

v2, l2 = [], []
for i in range(N2):
    v, l = map(int, input().split())
    v2.append(v)
    l2.append(l)

one, two = 0, 0
one_left, two_left = 0, 0
ans = 0
i = 0
while i < L:
    if l1[one] - (i - one_left) < l2[two] - (i - two_left):
        mn = l1[one] - (i - one_left)
        one_left += l1[one]
        one += 1
        if v1[one - 1] == v2[two]:
            ans += mn
    elif l1[one] - (i - one_left) > l2[two] - (i - two_left):
        mn = l2[two] - (i - two_left)
        two_left += l2[two]
        two += 1
        if v1[one] == v2[two - 1]:
            ans += mn
    else:
        mn = l2[two] - (i - two_left)
        one_left += l1[one]
        two_left += l2[two]
        one += 1
        two += 1
        if v1[one - 1] == v2[two - 1]:
            ans += mn
    i += mn

print(ans)
