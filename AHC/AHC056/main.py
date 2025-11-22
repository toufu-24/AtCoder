import sys
import collections

input = sys.stdin.readline

def solve():
    N, K, T = map(int, input().split())
    v_walls = [input().strip() for _ in range(N)]
    h_walls = [input().strip() for _ in range(N - 1)]
    targets = [tuple(map(int, input().split())) for _ in range(K)]

    def can_move_check(i, j, d):
        if d == 'U':
            if i == 0: return False
            return h_walls[i - 1][j] == '0'
        elif d == 'D':
            if i == N - 1: return False
            return h_walls[i][j] == '0'
        elif d == 'L':
            if j == 0: return False
            return v_walls[i][j - 1] == '0'
        elif d == 'R':
            if j == N - 1: return False
            return v_walls[i][j] == '0'
        return False

    MOVES_COORD = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}
    # 逆移動方向
    REVERSE_MOVES = {'U': 'D', 'D': 'U', 'L': 'R', 'R': 'L', 'S': 'S'}

    # --- 色の定義 ---
    EMPTY = 0
    PATH_U = 1 # 次は上に動くべき経路セル (偶数タスク/奇数タスク共通)
    PATH_D = 2 # 次は下に動くべき経路セル
    PATH_L = 3 # 次は左に動くべき経路セル
    PATH_R = 4 # 次は右に動くべき経路セル
    GOAL = 5   # 現在のタスクの目的地

    C = 6
    Q = K + 1 # 状態0..K-1がタスク中、Kが完了状態

    # --- 1. 全区間の最短経路と方向付けを事前計算 ---
    # path_directions[k][r][c] = k番目のタスク (x_k -> x_{k+1}) で (r,c) から次に行く方向
    path_directions = [] 

    for k_task in range(K - 1): # タスク k=0 から K-2 まで
        start_r, start_c = targets[k_task]
        goal_r, goal_c = targets[k_task + 1]

        # BFSで goal_r, goal_c から逆向きに最短経路を探索し、各セルから goal への方向を記録
        # (r, c) から goal へ向かう方向を move_map[r][c] に保存
        move_map = [['S'] * N for _ in range(N)]
        q_bfs = collections.deque([(goal_r, goal_c)])
        visited = [[False] * N for _ in range(N)]
        visited[goal_r][goal_c] = True
        
        # 逆向きBFSなので、move_map[nr][nc] には (nr,nc) から (r,c) への方向が記録される
        while q_bfs:
            r, c = q_bfs.popleft()
            for d_char, (dr, dc) in MOVES_COORD.items():
                nr, nc = r - dr, c - dc # 逆方向の隣接セル
                if not (0 <= nr < N and 0 <= nc < N):
                    continue
                
                # nr, nc から r, c へ移動可能で、かつ未訪問なら
                if can_move_check(nr, nc, d_char) and not visited[nr][nc]:
                    visited[nr][nc] = True
                    move_map[nr][nc] = d_char # (nr,nc) からこの方向に動けばゴールに近づく
                    q_bfs.append((nr, nc))
        
        path_directions.append(move_map)

    # --- 2. 初期盤面 s[i][j] の生成 ---
    # 全セルを EMPTY で初期化
    initial_board = [[EMPTY] * N for _ in range(N)]

    # 各タスク k_task = 0..K-2 について、経路の色をボードに書き込む
    # この例では、PATH_0_X と PATH_1_X の区別を無くし、GOAL で目的地を示す
    for k_task in range(K - 1):
        sr, sc = targets[k_task] # 始点
        gr, gc = targets[k_task + 1] # 終点

        curr_r, curr_c = sr, sc
        
        # 始点から終点までパスを辿って色を塗る
        while (curr_r, curr_c) != (gr, gc):
            direction_char = path_directions[k_task][curr_r][curr_c]
            
            # 経路の方向に合わせて色を塗る
            if direction_char == 'U': initial_board[curr_r][curr_c] = PATH_U
            elif direction_char == 'D': initial_board[curr_r][curr_c] = PATH_D
            elif direction_char == 'L': initial_board[curr_r][curr_c] = PATH_L
            elif direction_char == 'R': initial_board[curr_r][curr_c] = PATH_R
            
            dr, dc = MOVES_COORD[direction_char]
            curr_r, curr_c = curr_r + dr, curr_c + dc
        
        # 終点（目的地）をGOAL色で塗る
        initial_board[gr][gc] = GOAL
    
    # ロボットの初期位置 (targets[0]) をGOALで塗る
    # これにより、ロボットはまず最初のGOALを踏んでタスク0を開始できる
    initial_board[targets[0][0]][targets[0][1]] = GOAL


    # --- 3. 遷移ルール M の設計 (実際に使用されるものだけを記録) ---
    defined_rules = {} # (c, q) -> (A, S, D)

    # ロボットの初期位置と状態
    current_r, current_c = targets[0]
    current_state = 0 # タスク 0 から開始

    for step_count in range(T):
        curr_cell_color = initial_board[current_r][current_c]
        curr_q = current_state

        if (curr_cell_color, curr_q) in defined_rules:
            # 既に定義済みのルールなら再利用
            A, S, D = defined_rules[(curr_cell_color, curr_q)]
        else:
            # 新しいルールを定義
            new_A = EMPTY # 基本的に通過したセルはEMPTYに塗りつぶす
            new_S = curr_q
            new_D = 'S' # デフォルトは停止

            if curr_q == K: # 全タスク完了状態
                new_A, new_S, new_D = curr_cell_color, K, 'S' # 色も状態も維持、停止
            elif curr_cell_color == GOAL: # 目的地に到着！
                new_A = EMPTY # 目的地をEMPTYに塗りつぶす
                new_S = curr_q + 1 # 次のタスクへ
                new_D = 'S' # 一旦停止
            elif curr_q % 2 == 0: # 偶数タスク (C=PATH_0_X を探す)
                if curr_cell_color == PATH_U: new_D = 'U'
                elif curr_cell_color == PATH_D: new_D = 'D'
                elif curr_cell_color == PATH_L: new_D = 'L'
                elif curr_cell_color == PATH_R: new_D = 'R'
                # 他の色 (PATH_1_X や EMPTY) の場合は S (停止)
            else: # 奇数タスク (C=PATH_1_X を探す)
                # この実装ではPATH_0_XとPATH_1_Xを同じ色にしているため、
                # 偶数タスクと同じPATH_*色を見て動く
                if curr_cell_color == PATH_U: new_D = 'U'
                elif curr_cell_color == PATH_D: new_D = 'D'
                elif curr_cell_color == PATH_L: new_D = 'L'
                elif curr_cell_color == PATH_R: new_D = 'R'
                # 他の色 (PATH_0_X や EMPTY) の場合は S (停止)
            
            A, S, D = new_A, new_S, new_D
            defined_rules[(curr_cell_color, curr_q)] = (A, S, D)
        
        # --- ルールを適用してロボットを動かす ---
        initial_board[current_r][current_c] = A # 現在のセルを塗り替え
        current_state = S # 状態を更新

        # 移動
        if D != 'S':
            dr, dc = MOVES_COORD[D]
            next_r, next_c = current_r + dr, current_c + dc
            if can_move_check(current_r, current_c, D): # 壁チェック
                 current_r, current_c = next_r, next_c
            # else: # 壁にぶつかった場合は current_r, current_c は変化せず、実質停止
            #     pass
            
        # 全タスク完了かつ最終目的地に到達したらシミュレーション終了
        if current_state == K and (current_r, current_c) == targets[K-1]:
            # 最後の停止ルールを念のため定義しておく
            if (initial_board[current_r][current_c], K) not in defined_rules:
                 defined_rules[(initial_board[current_r][current_c], K)] = (initial_board[current_r][current_c], K, 'S')
            break
            

    # --- 4. 結果出力 ---
    print(C, Q, len(defined_rules))
    for r in range(N):
        print(' '.join(map(str, initial_board[r])))
    
    for (c_in, q_in), (A_out, S_out, D_out) in defined_rules.items():
        print(c_in, q_in, A_out, S_out, D_out)

solve()