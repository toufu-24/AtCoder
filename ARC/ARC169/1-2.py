N = int(input())
A = list(map(int, input().split()))
P = list(map(int, input().split()))

st = set()
after = A.copy()
a_0_senni = []
a_0_senni.append(A[0])
cnt = 0
for _ in range(10**2.5):
    for i in range(1, N):
        after[P[i - 1] - 1] += after[i]
        if P[i - 1] - 1 == 0:
            if after[0] in st:
                break
            st.add(after[0])
        a_0_senni.append(after[0])
        cnt += 1
    else:
        continue
    break

if a_0_senni[10**100 % cnt] > 0:
    print('+')
elif a_0_senni[10**100 % cnt] < 0:
    print('-')
else:
    print(0)