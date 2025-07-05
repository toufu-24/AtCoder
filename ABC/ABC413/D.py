from fractions import Fraction

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort(key=abs)
    ans = True
    hi = Fraction(a[1], a[0])
    for i in range(2, n):
        if Fraction(a[i], a[i - 1]) == hi:
            continue
        else:
            ans = False
            break

    # absが全部同じのとき
    if not ans and all(abs(x) == abs(a[0]) for x in a):
        minus = 0
        plus = 0
        for i in range(n):
            if a[i] < 0:
                minus += 1
            else:
                plus += 1
        if minus == plus or minus == plus + 1 or minus + 1 == plus:
            ans = True
        else:
            ans = False

    if ans:
        print("Yes")
    else:
        print("No")
