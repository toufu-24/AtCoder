from ortools.sat.python import cp_model
import sys


def solve():
    input = sys.stdin.readline
    N = int(input())

    model = cp_model.CpModel()

    # x, y の探索範囲は [1, 10^6] とする（N の最大値が 10^18 であることから）
    max_val = 10**6
    x = model.NewIntVar(1, max_val, "x")
    y = model.NewIntVar(1, max_val, "y")

    # x^3, y^3 を表現するための補助変数
    # x^3 の最大値は max_val^3 なのでその範囲で定義
    x_cube = model.NewIntVar(1, max_val**3, "x_cube")
    y_cube = model.NewIntVar(1, max_val**3, "y_cube")

    # 直接3変数の乗算制約は使えないため，2段階で x^3 = (x*x)*x を実現
    x_sq = model.NewIntVar(1, max_val**2, "x_sq")
    model.AddMultiplicationEquality(x_sq, [x, x])
    model.AddMultiplicationEquality(x_cube, [x_sq, x])

    y_sq = model.NewIntVar(1, max_val**2, "y_sq")
    model.AddMultiplicationEquality(y_sq, [y, y])
    model.AddMultiplicationEquality(y_cube, [y_sq, y])

    # 制約 x^3 - y^3 = N を追加
    model.Add(x_cube - y_cube == N)

    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL or status == cp_model.FEASIBLE:
        print(solver.Value(x), solver.Value(y))
    else:
        print(-1)


if __name__ == "__main__":
    solve()
