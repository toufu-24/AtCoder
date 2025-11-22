import sys
import collections

# Set higher recursion depth for deep paths if needed, though BFS avoids this
sys.setrecursionlimit(2000)

def solve():
    # --- 1. Read Input ---
    N, K, T = map(int, sys.stdin.readline().split())
    v_walls = [sys.stdin.readline().strip() for _ in range(N)]
    h_walls = [sys.stdin.readline().strip() for _ in range(N - 1)]
    targets = [tuple(map(int, sys.stdin.readline().split())) for _ in range(K)]

    # Add a dummy N-th row to h_walls to simplify can_move
    h_walls.append('1' * N)

    # --- 2. Helper Function for Wall Check ---
    # (i, j) is the *starting* cell
    def can_move(i, j, d):
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
        elif d == 'S':
            return True
        return False

    # Possible moves and their opposites
    MOVES = {
        'U': (-1, 0),
        'D': (1, 0),
        'L': (0, -1),
        'R': (0, 1),
    }
    # Used for BFS from goal
    REVERSE_MOVES = {
        'U': 'D',
        'D': 'U',
        'L': 'R',
        'R': 'L',
    }

    # --- 3. Precomputation: All-Pairs Shortest Path Moves ---
    
    # all_moves[q][i][j] = best move from (i, j) to get to targets[q+1]
    all_moves = [] 

    for q in range(K - 1): # For each goal from x_1 to x_{K-1}
        goal_r, goal_c = targets[q + 1]
        
        # dist[i][j] = distance from (i, j) to this goal
        dist = [[-1] * N for _ in range(N)]
        
        # moves_for_q[i][j] = best move from (i, j) for this goal
        moves_for_q = [['S'] * N for _ in range(N)]
        
        queue = collections.deque([(goal_r, goal_c)])
        dist[goal_r][goal_c] = 0
        
        # BFS from the goal
        while queue:
            r, c = queue.popleft()
            
            for move_char, (dr, dc) in MOVES.items():
                # We check move from (nr, nc) *to* (r, c)
                nr, nc = r - dr, c - dc # Neighbor cell
                
                # Check bounds
                if not (0 <= nr < N and 0 <= nc < N):
                    continue
                
                # If we can move from neighbor *to* current cell and it's unvisited
                if can_move(nr, nc, move_char) and dist[nr][nc] == -1:
                    dist[nr][nc] = dist[r][c] + 1
                    moves_for_q[nr][nc] = move_char # This is the move from (nr, nc)
                    queue.append((nr, nc))
                    
        all_moves.append(moves_for_q)

    # --- 4. Simulation to Generate Rules ---
    
    C = N * N
    Q = K
    
    # Initial board: s[i][j] = i*N + j
    s = [[(i * N + j) for j in range(N)] for i in range(N)]
    
    rules = {} # Use a dict to store unique rules: (c, q) -> (A, S, D)
    
    current_r, current_c = targets[0]
    current_state = 0 # State q=0 means goal is targets[1]
    
    for _ in range(T):
        pos = (current_r, current_c)
        c = current_r * N + current_c
        q = current_state
        
        if (c, q) in rules:
            # Rule already exists, just apply it
            _, new_state, move = rules[(c, q)]
        
        else:
            # --- Define a new rule for (c, q) ---
            if q == K - 1:
                # Done state
                new_state = K - 1
                move = 'S'
            else:
                # q < K-1, means we are going to targets[q+1]
                goal = targets[q + 1]
                
                if pos != goal:
                    # Not at goal, just move
                    new_state = q
                    move = all_moves[q][current_r][current_c]
                else:
                    # Arrived at goal!
                    new_state = q + 1
                    if new_state == K - 1:
                        # This was the last goal
                        move = 'S'
                    else:
                        # Arrived at intermediate goal,
                        # get move for *next* goal (q+1)
                        move = all_moves[new_state][current_r][current_c]
            
            # Store the new rule
            rules[(c, q)] = (c, new_state, move)
        
        # --- Apply the rule ---
        current_state = new_state
        if can_move(current_r, current_c, move):
            if move == 'U': current_r -= 1
            elif move == 'D': current_r += 1
            elif move == 'L': current_c -= 1
            elif move == 'R': current_c += 1
            # If move is 'S', (r, c) don't change
            
        if current_state == K - 1 and (current_r, current_c) == targets[K-1]:
            # We have reached the final state at the final target.
            # We can stop simulating, but must add the final "stay" rule.
            final_c = current_r * N + current_c
            if (final_c, K-1) not in rules:
                 rules[(final_c, K-1)] = (final_c, K-1, 'S')
            break

    # --- 5. Output ---
    print(C, Q, len(rules))
    
    for i in range(N):
        print(' '.join(map(str, s[i])))
        
    for (c, q), (A, S, D) in rules.items():
        print(c, q, A, S, D)

# Run the solver
solve()