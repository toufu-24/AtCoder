inp = input()
from itertools import product

plusminus = ["+", "-"]
for bit in product(plusminus, repeat=3):
    s = ""
    for i in range(len(inp) - 1):
        s += inp[i]
        s += bit[i]
    s += inp[-1]
    if eval(s) == 7:
        print(s + "=7")
        exit()

print("No")
