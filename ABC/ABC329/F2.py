N, Q = map(int, input().split())
C = list(map(int, input().split()))
box = [0] * N
for i in range(N):
    box[i] += 1 << (C[i] - 1)
for q in range(Q):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    box[b] |= box[a]
    box[a] = 0
    print(bin(box[b]).count("1"))
