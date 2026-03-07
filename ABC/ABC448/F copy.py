# https://qiita.com/NamiSakamoto/items/998dc7203e60dd600d3f

import pulp

# ５地点
# points = [
#     ("P1", 35.6804, 139.7690),
#     ("P2", 35.6916, 139.7003),
#     ("P3", 35.6586, 139.7454),
#     ("P4", 35.6897, 139.6921),
#     ("P5", 35.6894, 139.6917),
# ]

n = int(input())
points = []
for i in range(n):
    x, y = map(int, input().split())
    s = "P" + str(i)
    points.append((s, x, y))


# 距離をユークリッド距離で定義
def euclidean_distance(p1, p2):
    return abs(p1[1] - p2[1]) + abs((p1[2] - p2[2]))


# 距離を辞書形式で保持
dist = {}
for i in range(n):
    for j in range(n):
        if i != j:
            dist[(i, j)] = euclidean_distance(points[i], points[j])
x = pulp.LpVariable.dicts("x", (range(n), range(n)), cat=pulp.LpBinary)

problem = pulp.LpProblem("TSP", pulp.LpMinimize)

# 目的関数: 移動距離の合計最小化
problem += pulp.lpSum(
    dist[(i, j)] * x[i][j] for i in range(n) for j in range(n) if i != j
)

# 各都市からの移動は一回
for i in range(n):
    problem += pulp.lpSum(x[i][j] for j in range(n) if i != j) == 1

# 各都市への移動も一回
for j in range(n):
    problem += pulp.lpSum(x[i][j] for i in range(n) if i != j) == 1

# サブツアー(部分巡回)除去用の変数 u[i]
# MTZ (Miller-Tucker-Zemlin)
u = pulp.LpVariable.dicts("u", range(n), lowBound=0, upBound=n - 1, cat=pulp.LpInteger)

# i=0 を出発都市と仮定してサブツアー除去
# i!=0, j!=0 の i->j 移動に対して: u[i] - u[j] + n*x[i][j] <= n-1
for i in range(1, n):
    for j in range(1, n):
        if i != j:
            problem += u[i] - u[j] + n * x[i][j] <= n - 1

# CBCソルバーを使用
problem.solve(pulp.PULP_CBC_CMD(msg=False, timeLimit=0.1))

# print("Status:", pulp.LpStatus[problem.status])
# print("Objective value (Total Distance) =", pulp.value(problem.objective))

# 解の取り出し
route = []
current_city = 0
route.append(current_city)
visited = set([current_city])

for _ in range(n - 1):
    for j in range(n):
        if j not in visited and pulp.value(x[current_city][j]) == 1:
            route.append(j)
            visited.add(j)
            current_city = j
            break

# # 最後に出発点に戻る
# for j in range(n):
#     if pulp.value(x[current_city][j]) == 1 and j == 0:
#         route.append(0)
#         break

# print("Route (city indices):", route)
# print("Route (city names):", [points[i][0] for i in route])

for p in route:
    print(p + 1, end=" ")
