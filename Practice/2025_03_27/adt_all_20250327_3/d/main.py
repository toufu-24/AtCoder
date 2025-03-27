a, m, l, r = map(int, input().split())
l -= a
r -= a
print(r // m - (l - 1) // m)
