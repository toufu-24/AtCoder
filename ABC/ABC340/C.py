N = int(input())
memo = {}
def f(n):
    if n == 1:
        return 0
    if n in memo:
        return memo[n]
    lower = n // 2
    upper = (n + 1) // 2
    memo[n] = f(lower) + f(upper) + n
    return memo[n]
print(f(N))
