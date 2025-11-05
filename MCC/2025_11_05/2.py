n = int(input())
x = []
y = []
for i in range(n):
    a, b = map(int, input().split())
    x.append(a)
    y.append(b)

from fractions import Fraction


def main():
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                try:
                    tmp1 = Fraction(x[i] - x[j], y[i] - y[j])
                    tmp2 = Fraction(x[k] - x[j], y[k] - y[j])
                    if tmp1 == tmp2:
                        print("Yes")
                        return
                except:
                    if y[i] == y[k]:
                        print("Yes")
                        return
    print("No")


main()
