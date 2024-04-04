A, M, L, R = map(int, input().split())
R -= A
L -= A
right = R // M
left = (L - 1) // M
tree = right - left
print(tree)
