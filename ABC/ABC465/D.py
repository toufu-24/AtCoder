t = int(input())
for _ in range(t):
    X, Y, K = map(int, input().split())
    x = X
    left = 0
    right = int(10**18)
    # xをkで割る or [k, k+1)倍する
    while abs(left - right) > 1:
        mid = (left + right) // 2
        # mid回 だけ割る
        xx = x // (K * mid)

        # 何回かけるか
        left2 = 0
        right2 = 70
        while abs(left2 - right2) > 1:
            mid2 = (left2 + right2) // 2
            # mid2回かけて範囲内か
            min_ra = xx * (K**mid2)
            if min_ra <= Y:
                right2 = mid2
            else:
                left2 = mid2

        # left2 回かければいい

