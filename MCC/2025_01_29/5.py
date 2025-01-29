s = input()

t = s[-3:]
if int(t) % 8 == 0:
    print("Yes")
    exit()

from itertools import permutations

for p in permutations(s, 3):
    num = int("".join(p))
    if num % 8 == 0:
        print("Yes")
        exit()
print("No")
