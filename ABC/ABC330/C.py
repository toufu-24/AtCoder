import bisect

D = int(input())
pows = []
for i in range(1, int(D**(0.5)) + 100):
    pows.append(i * i)
ans = 10**18
for i in range(len(pows)):
    idx = bisect.bisect_left(pows, D - pows[i])
    idx2 = idx - 1
    idx3 = bisect.bisect_right(pows, D - pows[i])
    if idx >= 0 and idx < len(pows):
        ans = min(ans, abs(pows[i] + pows[idx] - D))
    if idx2 >= 0:
        ans = min(ans, abs(pows[i] + pows[idx2] - D))
    if idx3 < len(pows):
        ans = min(ans, abs(pows[i] + pows[idx3] - D))
print(ans)
