L, R = map(int, input().split())
ans = []
while True:
    if L == R:
        break
    if L == 0:
        # Rを超えない最大の2のべき乗を探す
        ok = 0
        ng = 64
        while ng - ok > 1:
            mid = (ok + ng) // 2
            if (1 << mid) <= R:
                ok = mid
            else:
                ng = mid
        ans.append([0, 1 << ok])
        L = 1 << ok
        continue

    l = L
    cnt = 0
    while l % 2 == 0:
        l //= 2
        cnt += 1
    if (1 << cnt) * (l + 1) <= R:
        ans.append([L, (1 << cnt) * (l + 1)])
        L = (1 << cnt) * (l + 1)
        continue
    ok = 0
    ng = cnt
    while ng - ok > 1:
        mid = (ok + ng) // 2
        tmp = (1 << mid) * (l * (1 << (cnt - mid)) + 1)
        if tmp <= R:
            ok = mid
        else:
            ng = mid
    ans.append([L, (1 << ok) * (l * (1 << (cnt - ok)) + 1)])
    L = (1 << ok) * (l * (1 << (cnt - ok)) + 1)

print(len(ans))
for l, r in ans:
    print(l, r)

