import numpy as np
from scipy.spatial.distance import cdist
from pulp import LpProblem, LpMinimize, LpVariable, lpSum, value, PULP_CBC_CMD


def constrained_kmeans(X, M, G_i):
    """
    制約付き K-Means を ILP で解く
    - X: ndarray, shape (N, D) - 入力データ (N個のデータポイント, D次元)
    - M: int - クラスタ数
    - G_i: list - 各クラスタに割り当てるデータポイント数のリスト

    出力:
    - labels: list - データポイントのクラスタ割当
    - centroids: ndarray - 各クラスタの最終的な重心
    """

    # データポイント数と次元数
    N, D = X.shape

    # 初期クラスタ中心をランダムに選択
    np.random.seed(42)
    centroids = X[np.random.choice(N, M, replace=False)]

    # 距離行列 (N x M): 各データポイントと各クラスタ中心の距離
    distances = cdist(X, centroids, metric="euclidean")

    # ILP 問題の定義
    prob = LpProblem("Constrained_KMeans", LpMinimize)

    # 変数定義: z[i, j] = 1 ならデータポイント j をクラスタ i に割り当てる
    z = LpVariable.dicts(
        "z", [(i, j) for i in range(M) for j in range(N)], cat="Binary"
    )

    # 目的関数: 距離の最小化
    prob += lpSum(z[i, j] * distances[j, i] for i in range(M) for j in range(N))

    # 制約1: 各データポイントは 1 つのクラスタにのみ割り当てる
    for j in range(N):
        prob += lpSum(z[i, j] for i in range(M)) == 1

    # 制約2: 各クラスタには G_i 個のデータポイントを割り当てる
    for i in range(M):
        prob += lpSum(z[i, j] for j in range(N)) == G_i[i]

    # ソルバーの設定：1.7秒のタイムリミットを設定
    solver = PULP_CBC_CMD(timeLimit=1.7, msg=False)
    prob.solve(solver)

    # 結果の取得（暫定解も含む）
    labels = np.zeros(N, dtype=int)
    for j in range(N):
        for i in range(M):
            # 変数の値が None になる場合もあるので注意
            if value(z[i, j]) is not None and value(z[i, j]) > 0.5:
                labels[j] = i

    # クラスタ中心の更新（暫定解に基づく）
    # new_centroids = np.zeros((M, D))
    # for i in range(M):
    #     cluster_points = X[labels == i]
    #     if len(cluster_points) > 0:
    #         new_centroids[i] = cluster_points.mean(axis=0)

    return labels


def calc_distance(city1, city2):
    """2つの都市間のユークリッド距離を計算する"""
    return ((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2) ** 0.5


def build_group_mst(group, cities):
    """
    グループ内の最小全域木を構築する

    Args:
        group (list): グループに属する都市のインデックスリスト
        cities (list): 都市の座標リスト [(x1, y1), (x2, y2), ...]

    Returns:
        list: 最小全域木の辺のリスト [(u, v), ...] ※u < vになるように格納
    """
    if len(group) <= 1:
        return []

    group_mst_edges = []
    possible_edges = []

    # グループ内の全ての都市ペアの辺を生成
    for i in range(len(group)):
        for j in range(i + 1, len(group)):
            dist = calc_distance(cities[group[i]], cities[group[j]])
            possible_edges.append((dist, group[i], group[j]))

    # 辺を距離でソート
    possible_edges.sort()

    # 最小全域木のクラスカル法
    N = len(cities)
    parent = list(range(N))

    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]

    for dist, u, v in possible_edges:
        pu = find(u)
        pv = find(v)
        if pu != pv:
            parent[pu] = pv
            group_mst_edges.append((min(u, v), max(u, v)))
            if len(group_mst_edges) == len(group) - 1:
                break

    return group_mst_edges


# --- サンプルデータでテスト ---
if __name__ == "__main__":
    # 入力例の形式: N, M, Q, L, W（ここでは Q, L, W は未使用）
    N, M, Q, L, W = map(int, input().split())
    # 各クラスタに割り当てるデータ数 G_i（合計は N と一致する必要があります）
    G = list(map(int, input().split()))
    lx, rx, ly, ry = [], [], [], []
    for _ in range(N):
        a, b, c, d = map(int, input().split())
        lx.append(a)
        rx.append(b)
        ly.append(c)
        ry.append(d)
    # 各データポイントの代表値として矩形の中心を使用
    X = []
    for i in range(N):
        X.append([(lx[i] + rx[i]) / 2, (ly[i] + ry[i]) / 2])
    X = np.array(X)

    # ILP によるクラスタリングの実行
    labels = constrained_kmeans(X, M, G)
    groups = [[] for _ in range(M)]
    for i, label in enumerate(labels):
        groups[label].append(i)
    # グループごとの最小全域木を構築
    mst_edges = [[] for _ in range(M)]
    # 各グループの最小全域木を構築
    for i, group in enumerate(groups):
        group_mst_edges = build_group_mst(group, X)
        mst_edges[i].extend(group_mst_edges)
    # 結果を出力
    print("!")
    for i in range(M):
        print(*groups[i])
        for u, v in mst_edges[i]:
            print(u, v)
