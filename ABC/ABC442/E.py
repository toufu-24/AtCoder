n, q = map(int, input().split())
x = []
y = []
for i in range(n):
    t, m = map(int, input().split())
    x.append(t)
    y.append(m)
from fractions import Fraction

angles = []  # tan
shogen = [0] * n
angle_shogen = [[], [], [], []]

for i in range(n):
    if x[i] != 0:
        angles.append(Fraction(y[i], x[i]))
    else:
        if y[i] >= 0:
            angles.append(float("inf"))
        else:
            angles.append(-float("inf"))

    if x[i] >= 0 and y[i] >= 0:
        shogen[i] = 0
    elif x[i] >= 0 and y[i] <= 0:
        shogen[i] = 1
    elif x[i] <= 0 and y[i] <= 0:
        shogen[i] = 2
    else:
        shogen[i] = 3

    angle_shogen[shogen[i]].append(angles[-1])

for i in range(4):
    if i < 2:
        angle_shogen[i] = sorted(angle_shogen[i])
        # angle_shogen[i] = sorted(angle_shogen[i], reverse=True)
    else:
        angle_shogen[i] = sorted(angle_shogen[i])

import bisect

for _ in range(q):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    ans = 0
    a_angle = angles[a]
    b_angle = angles[b]

    for i in range(4):
        if i != shogen[a]:
            continue
        if i < 2:
            # a_angleがあるか，あるならそのインデックス
            a_bi = bisect.bisect_left(angle_shogen[i], a_angle)
            if a_bi != len(angle_shogen[i]):
                a_idx = a_bi
                a_sho = i
        else:
            a_bi = bisect.bisect_left(angle_shogen[i], a_angle)
            if a_bi != len(angle_shogen[i]):
                a_bi = bisect.bisect_right(angle_shogen[i], a_angle) - 1
                a_idx = a_bi
                a_sho = i

    for i in range(4):
        if i != shogen[b]:
            continue
        if i < 2:
            b_bi = bisect.bisect_left(angle_shogen[i], b_angle)
            if b_bi != len(angle_shogen[i]):
                b_bi = bisect.bisect_right(angle_shogen[i], b_angle) - 1
                b_idx = b_bi
                b_sho = i
        else:
            b_bi = bisect.bisect_left(angle_shogen[i], b_angle)
            if b_bi != len(angle_shogen[i]):
                b_idx = b_bi
                b_sho = i
    print(a_sho, a_idx, b_sho, b_idx)
    get = False
    already = False
    for ii in range(8):
        print(ans)
        print(get, already)
        i = ii % 4
        if a_sho == i:
            if already:
                break
            get = True
            already = True
            if i < 2:
                ans += a_idx + 1
            else:
                ans += len(angle_shogen[i]) - a_idx
        elif b_sho == i and get:
            get = False
            if i < 2:
                ans += len(angle_shogen[i]) - b_idx
            else:
                ans += b_idx + 1
        elif get:
            ans += len(angle_shogen[i])

    print(ans)
    print("-----------")
