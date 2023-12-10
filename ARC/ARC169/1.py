import matplotlib.pyplot as plt

N = int(input())
A = list(map(int, input().split()))
P = list(map(int, input().split()))

st = set()
after = A.copy()
a_0_senni = []
a_0_senni.append(A[0])
cnt = 0
for _ in range(int(10**2)):
    for i in range(1, N):
        after[P[i - 1] - 1] += after[i]
    a_0_senni.append(after[0])
    cnt += 1

if a_0_senni[10**100 % cnt] > 0:
    print("+")
elif a_0_senni[10**100 % cnt] < 0:
    print("-")
else:
    print(0)

# plt.plot(a_0_senni)
# plt.show()
