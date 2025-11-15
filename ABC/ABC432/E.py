n, q = [int(x) for x in input().split()]
a = list([int(x) for x in input().split()])
from sortedcontainers import SortedList


# https://qiita.com/AkariLuminous/items/f2f7930e7f67963f0493
class Fenwick_Tree:
    def __init__(self, n):
        self._n = n
        self.data = [0] * n

    def add(self, p, x):
        assert 0 <= p < self._n
        p += 1
        while p <= self._n:
            self.data[p - 1] += x
            p += p & -p

    def sum(self, l, r):
        assert 0 <= l <= r <= self._n
        return self._sum(r) - self._sum(l)

    def _sum(self, r):
        s = 0
        while r > 0:
            s += self.data[r - 1]
            r -= r & -r
        return s


# seg = SegmentTree[int](lambda a, b: a + b, lambda: 0, [0] * 10**6)
seg = Fenwick_Tree(10**6)
for a_i in a:
    # seg[a_i] += a_i
    seg.add(a_i, a_i)
sl = SortedList(a)
while q > 0:
    q -= 1
    op, x, y = [int(x) for x in input().split()]
    if op == 1:
        x -= 1
        # seg[a[x]] -= a[x]
        # seg[y] += y
        seg.add(a[x], -a[x])
        seg.add(y, y)
        sl.remove(a[x])
        sl.add(y)
        a[x] = y
    else:
        l = x
        r = y
        if l >= r:
            print(l * n)
            continue
        left = sl.bisect_right(l)
        right = sl.bisect_left(r)
        print(left * l + seg.sum(l + 1, r) + (n - right) * r)
