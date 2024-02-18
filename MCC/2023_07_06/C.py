import math
s = int(input())
t = int(pow(s, 1/3))

a = 0
tt = 0
while True:
    if s % (t + a) == 0:
        tt = t + a
        break
    if s % (t - a) == 0:
        tt = t - a
        break
    a += 1

dd = s / tt
r = int(math.sqrt(dd))

a = 0
while True:
    if dd % (r + a) == 0:
        rr = r + a
        break
    if dd % (r - a) == 0:
        rr = r - a
        break
    a += 1


print(tt + 2 * rr)