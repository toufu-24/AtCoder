import bisect
from numba import jit


@jit
def main():
    N = int(input())
    A = []
    for i in range(N):
        A.append(int(input()))
    A = sorted(A)

    cnt = 0
    for i in range(N):
        for j in range(i, N):
            tmp = A[i] * A[j]
            if(tmp > A[-1]):
                break
            lidx = bisect.bisect_left(A, tmp)
            ridx = bisect.bisect_right(A, tmp)
            cnt += ridx - lidx
    print(cnt)


main()
