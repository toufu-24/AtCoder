from fractions import Fraction
import numpy as np

t = int(input())
for _ in range(t):
    px, py, qx, qy, rx, ry, sx, sy = map(int, input().split())
    p = (px, py)
    q = (qx, qy)
    r = (rx, ry)
    s = (sx, sy)
    if px > qx:
        px, qx = qx, px
        py, qy = qy, py
        p, q = q, p
    if rx > sx:
        rx, sx = sx, rx
        ry, sy = sy, ry
        r, s = s, r

    same = p == r and q == s
    if same:
        print("Yes")
        continue
    if qx == px:
        a_kata = np.inf
    else:
        a_kata = Fraction((qy - py), (qx - px))
    if rx == sx:
        b_kata = np.inf
    else:
        b_kata = Fraction((ry - sy), (rx - sx))
    isheikou = a_kata == b_kata

    a_mid = (Fraction(qx + px, 2), Fraction(qy + py, 2))
    b_mid = (Fraction(rx + sx, 2), Fraction(ry + sy, 2))
    if a_mid[0] > b_mid[0]:
        a_mid, b_mid = b_mid, a_mid
    # 中点同士の傾きがaか
    if not isheikou:
        print("Yes")
    elif a_mid == b_mid:
        print("Yes")
    elif a_kata == 0:
        if a_mid[0] == b_mid[0]:
            print("Yes")
        else:
            print("No")
    elif a_kata == np.inf:
        if a_mid[1] == b_mid[1]:
            print("Yes")
        else:
            print("No")
    elif a_mid[0] == b_mid[0]:
        print("No")
    elif Fraction(b_mid[1] - a_mid[1], b_mid[0] - a_mid[0]) == -Fraction(1, a_kata):
        print("Yes")
    else:
        print("No")
