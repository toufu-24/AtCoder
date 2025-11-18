import sys
import collections

# 入力を高速に読み込む
input = sys.stdin.readline


def solve():
    # --- 1. 入力と壁情報のセットアップ ---
    N, K, T = map(int, input().split())
    v_walls = [input().strip() for _ in range(N)]
    h_walls = [input().strip() for _ in range(N - 1)]  # <--- (N-1)行のまま
    targets = [tuple(map(int, input().split())) for _ in range(K)]

    # h_walls.append('1' * N) # <--- この行を削除（またはコメントアウト）してください

    def can_move(i, j, d):
        if d == "U":
            if i == 0:
                return False
            return h_walls[i - 1][j] == "0"
        elif d == "D":
            if i == N - 1:
                return False
            return h_walls[i][j] == "0"  # h_walls (N-1行) の 0..N-2 を参照
        elif d == "L":
            if j == 0:
                return False
            return v_walls[i][j - 1] == "0"
        elif d == "R":
            if j == N - 1:
                return False
            return v_walls[i][j] == "0"
        elif d == "S":
            return True
        return False

    # ... (以降のコードは変更なし) ...
    MOVES = {"U": (-1, 0), "D": (1, 0), "L": (0, -1), "R": (0, 1)}

    # --- Step 1: 事前計算 (全目的地への最適手をBFS) ---
    all_moves = []

    for q in range(K - 1):  # 目的地 x_1 から x_{K-1} まで
        goal_r, goal_c = targets[q + 1]
        dist = [[-1] * N for _ in range(N)]
        moves_for_q = [["S"] * N for _ in range(N)]

        queue = collections.deque([(goal_r, goal_c)])
        dist[goal_r][goal_c] = 0

        while queue:
            r, c = queue.popleft()
            for move_char, (dr, dc) in MOVES.items():
                nr, nc = r - dr, c - dc  # 逆から辿る
                if not (0 <= nr < N and 0 <= nc < N):
                    continue

                if can_move(nr, nc, move_char) and dist[nr][nc] == -1:
                    dist[nr][nc] = dist[r][c] + 1
                    moves_for_q[nr][nc] = move_char
                    queue.append((nr, nc))

        all_moves.append(moves_for_q)

    # --- Step 2: シグネチャ生成と色のマッピング ---

    signature_to_color = {}
    color_to_signature = {}
    new_cell_colors = [[0] * N for _ in range(N)]
    new_color_id = 0

    for r in range(N):
        for c in range(N):
            move_vec = tuple(all_moves[q][r][c] for q in range(K - 1))
            goal_vec = tuple((r, c) == targets[q + 1] for q in range(K - 1))

            sig = (move_vec, goal_vec)

            if sig not in signature_to_color:
                color = new_color_id
                signature_to_color[sig] = color
                color_to_signature[color] = sig
                new_color_id += 1
            else:
                color = signature_to_color[sig]

            new_cell_colors[r][c] = color

    C = new_color_id
    Q = K

    # --- Step 3: ルール定義 (遅延評価) ---
    defined_rules = {}

    def get_rule(c, q):
        if (c, q) in defined_rules:
            return defined_rules[(c, q)]

        sig = color_to_signature[c]
        move_vec, goal_vec = sig

        if q == K - 1:
            A, S, D = c, K - 1, "S"
        else:
            is_goal = goal_vec[q]
            if not is_goal:
                A, S, D = c, q, move_vec[q]
            else:
                new_state = q + 1
                if new_state == K - 1:
                    A, S, D = c, new_state, "S"
                else:
                    A, S, D = c, new_state, move_vec[q + 1]

        rule = (A, S, D)
        defined_rules[(c, q)] = rule
        return rule

    # --- Step 4: シミュレーション (使用ルールの収集) ---
    current_r, current_c = targets[0]
    current_state = 0

    # デバッグ: 初期位置が範囲外でないか確認
    if not (0 <= current_r < N and 0 <= current_c < N):
        print(
            f"Error: Initial target {targets[0]} is out of bounds for N={N}",
            file=sys.stderr,
        )
        sys.exit(1)

    for _ in range(T):
        # エラーの発生箇所
        if not (0 <= current_r < N and 0 <= current_c < N):
            # このエラーが発生した場合、can_move または get_rule のロジックが誤っている
            print(
                f"Error: Robot went out of bounds to ({current_r}, {current_c})",
                file=sys.stderr,
            )
            sys.exit(1)

        c = new_cell_colors[current_r][current_c]
        q = current_state

        A, S, D = get_rule(c, q)

        current_state = S

        if can_move(current_r, current_c, D):
            if D == "U":
                current_r -= 1
            elif D == "D":
                current_r += 1
            elif D == "L":
                current_c -= 1
            elif D == "R":
                current_c += 1

        if current_state == K - 1 and (current_r, current_c) == targets[K - 1]:
            get_rule(new_cell_colors[current_r][current_c], K - 1)
            break

    # --- Step 5: 出力 ---
    print(C, Q, len(defined_rules))

    for r in range(N):
        print(" ".join(map(str, new_cell_colors[r])))

    for (c, q), (A, S, D) in defined_rules.items():
        print(c, q, A, S, D)


solve()
