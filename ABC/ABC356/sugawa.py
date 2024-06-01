import itertools

N, M, K = map(int, input().split())

arieru = set()
arienai = set()

for i in range(M):
    C, *AR = input().split()
    C = int(C)
    A, R = map(int, AR[:-1]), AR[-1]
    A = sorted(A)
    if R == "o":
        arieru |= set(itertools.combinations(A, K))
    else:
        arienai |= set(itertools.combinations(A, K))

arienai -= arieru
ans = (1 << N) - len(arienai)
print(ans)
