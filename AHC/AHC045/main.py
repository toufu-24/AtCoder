import numpy as np
from scipy.spatial import distance_matrix
from sklearn.cluster import KMeans

N, M, Q, L, W = map(int, input().split())
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

import sys

print("input", file=sys.stderr)

# 点の座標を与える
points = np.array(X)

# 距離行列の計算
D = distance_matrix(points, points)

# 初期クラスタリング
kmeans = KMeans(n_clusters=M, random_state=42).fit(points)
labels = kmeans.labels_

# サイズ制約の調整
groups = [[] for _ in range(M)]
for i, label in enumerate(labels):
    groups[label].append(i)


# サイズの調整処理
def adjust_groups(groups, D, G):
    M = len(G)
    # 各グループについて余分な点を一括処理
    for i in range(M):
        excess = len(groups[i]) - G[i]
        if excess > 0:
            # 現在のグループ内の各点について、グループ内の他点との距離の総和を計算し、降順にソート
            candidate_points = sorted(
                groups[i], key=lambda p: np.sum(D[p, groups[i]]), reverse=True
            )
            # 余分な点を先頭から処理
            for point in candidate_points[:excess]:
                if point in groups[i]:  # 既に削除済みでないかチェック
                    groups[i].remove(point)
                    # 割り当て可能なグループ（サイズに余裕があるグループ）を抽出
                    candidate_groups = [j for j in range(M) if len(groups[j]) < G[j]]
                    if candidate_groups:
                        # 各候補グループに対して、pointとそのグループ内の点との距離の総和を計算
                        candidate_sums = [
                            np.sum(D[point, groups[j]]) if groups[j] else 0
                            for j in candidate_groups
                        ]
                        # 距離の総和が最小となるグループへ割り当てる
                        chosen_idx = np.argmin(candidate_sums)
                        groups[candidate_groups[chosen_idx]].append(point)
                    else:
                        # 割り当て可能なグループが無い場合（矛盾状態）、元に戻す
                        groups[i].append(point)
    return groups


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


print("initial_groups", file=sys.stderr)
# 調整後のグループ
final_groups = adjust_groups(groups, D, G)
print("final_groups", file=sys.stderr)
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
