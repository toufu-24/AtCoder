from collections import deque

class AnsData:
    def __init__(self):
        # 信号操作の回数
        # 小さい方が良い
        self.score = 0
        self.A = []
        self.ans = []

def calc_score(A, paths, lb):
    res = AnsData()
    res.A = A[:]
    B = [-1] * lb
    la = len(A)
    n = 600
    t = 601
    score = 0
    ans = []
    
    for i in range(t - 1):
        path = paths[i]
        for j in range(len(path)):
            if path[j] not in B:
                # 信号操作
                res.score += 1
                a_idx = A.index(path[j])
                if a_idx + lb > la:
                    res.ans.append(f"s {lb} {la - lb} 0")
                    for k in range(lb):
                        B[k] = A[la - lb + k]
                else:
                    res.ans.append(f"s {lb} {a_idx} 0")
                    for k in range(lb):
                        B[k] = A[a_idx + k]

            # 移動
            res.ans.append(f"m {path[j]}")
    
    return res

def main():
    _n, m, _t, la, lb = map(int, input().split())
    n = 600
    t = 601
    graph = [[] for _ in range(n)]
    
    for _ in range(m):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)
    
    target = list(map(int, input().split()))
    target = [0] + target
    # パスの探索
    paths = [[] for _ in range(t)]
    for i in range(t - 1):
        # target[i] -> target[i+1]に移動
        que = deque([target[i]])
        dist = [1e9] * n
        dist[target[i]] = 0
        
        while que:
            v = que.popleft()
            for u in graph[v]:
                if dist[u] != 1e9:
                    continue
                dist[u] = dist[v] + 1
                if u == target[i + 1]:
                    que = deque()
                    break
                que.append(u)
        
        v = target[i + 1]
        path = []
        while v != target[i]:
            path.append(v)
            for u in graph[v]:
                if dist[u] == dist[v] - 1:
                    v = u
                    break
        
        path.reverse()
        paths[i] = path
    
    # Aの初期化
    A = [0] * la
    B = [-1] * lb
    unused = set(range(n))
    
    # pathを使ってAを埋める
    cnt = 0
    for i in range(t - 1):
        path = paths[i]
        for j in range(len(path)):
            if cnt + len(unused) == la:
                for x in unused:
                    A[cnt] = x
                    cnt += 1
                break
            A[cnt] = path[j]
            cnt += 1
            unused.discard(path[j])
        
        if cnt == la:
            break
    
    # 移動&信号操作
    res = calc_score(A, paths, lb)

    print(" ".join(map(str, res.A)))
    for x in res.ans:
        print(x)

if __name__ == "__main__":
    main()
