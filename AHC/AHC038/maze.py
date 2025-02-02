import gym
import numpy as np
import random
from gym import spaces
import matplotlib.pyplot as plt


def generate_maze(height, width, start_pos, goal_pos):
    maze = np.ones((height, width))  # すべてを壁で初期化

    # 穴掘り法で迷路を生成
    def carve_passages(x, y):
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # 右、下、左、上
        random.shuffle(directions)  # ランダムに方向をシャッフル

        for dx, dy in directions:
            nx, ny = x + dx * 2, y + dy * 2  # 2マス先の位置を計算
            if 1 <= nx < height - 1 and 1 <= ny < width - 1 and maze[nx, ny] == 1:
                maze[x + dx][y + dy] = 0  # 壁を壊す
                maze[nx][ny] = 0  # 新しい位置を通行可能にする
                carve_passages(nx, ny)  # 再帰的に通路を掘る

    carve_passages(1, 1)  # スタート位置から通路を掘り始める
    # スタートとゴールの位置を設定
    maze[start_pos[0], start_pos[1]] = 0  # スタート位置は通行可能
    maze[goal_pos[0], goal_pos[1]] = 0  # ゴール位置も通行可能

    # 迷路を表示
    for i in range(height):
        for j in range(width):
            if maze[i, j] == 0:
                print(".", end="")  # 通路
            else:
                print("#", end="")  # 壁
        print()  # 次の行へ

    return maze


from collections import deque
class MazeEnv(gym.Env):
    def __init__(self):
        super(MazeEnv, self).__init__()

        # 迷路のサイズを定義
        self.height = 30
        self.width = 30

        # アクション空間を定義（上、右、下、左）
        self.action_space = spaces.Discrete(4)

        # 観測空間を定義（現在の位置）
        self.observation_space = spaces.Box(
            low=0, high=max(self.height, self.width), shape=(2,), dtype=np.float32
        )

        # 迷路の初期化
        self.maze = generate_maze(
            self.height, self.width, [1, 1], [self.height - 3, self.width - 3]
        )

        # スタートとゴールの位置
        self.start_pos = np.array([1, 1])
        self.goal_pos = np.array([self.height - 3, self.width - 3])

        # 現在の位置
        self.current_pos = None

    def reset(self):
        # エージェントをスタート位置にリセット
        self.current_pos = self.start_pos.copy()
        return self.current_pos

    def step(self, action):
        # 行動に基づいて次の位置を計算
        next_pos = self.current_pos.copy()
        if action == 0:  # 上
            next_pos[0] = max(0, next_pos[0] - 1)
        elif action == 1:  # 右
            next_pos[1] = min(self.width - 1, next_pos[1] + 1)
        elif action == 2:  # 下
            next_pos[0] = min(self.height - 1, next_pos[0] + 1)
        elif action == 3:  # 左
            next_pos[1] = max(0, next_pos[1] - 1)

        # 壁との衝突チェック
        if self.maze[next_pos[0], next_pos[1]] == 0:
            self.current_pos = next_pos

        # 報酬の計算
        if np.array_equal(self.current_pos, self.goal_pos):
            reward = 1000
            done = True
        else:
            reward = 0
            que = deque()
            que.append(self.current_pos)
            dist = np.ones((self.height, self.width)) * 1e9
            dist[self.current_pos[0], self.current_pos[1]] = 0
            while que:
                now = que.pop()
                for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                    nx, ny = now[0] + dx, now[1] + dy
                    if 0 <= nx < self.height and 0 <= ny < self.width and self.maze[nx, ny] == 0 and dist[nx, ny] == 1e9:
                        dist[nx, ny] = dist[now[0], now[1]] + 1
                        que.append((nx, ny))
            reward = -dist[self.goal_pos[0], self.goal_pos[1]]
            done = False

        return self.current_pos, reward, done, {}

    def render(self):
        maze_render = self.maze.copy()
        maze_render[self.start_pos[0], self.start_pos[1]] = 2
        maze_render[self.goal_pos[0], self.goal_pos[1]] = 3
        maze_render[self.current_pos[0], self.current_pos[1]] = 4

        plt.imshow(maze_render)
        plt.show()


class QLearningAgent:
    def __init__(self, env):
        self.env = env
        self.q_table = {}
        self.alpha = 0.1  # 学習率
        self.gamma = 0.9  # 割引率
        self.epsilon = 0.1  # ε-greedy法のパラメータ

    def get_key(self, state):
        return tuple(state)

    def get_action(self, state):
        if random.random() < self.epsilon:
            return self.env.action_space.sample()

        state_key = self.get_key(state)
        if state_key not in self.q_table:
            self.q_table[state_key] = np.zeros(self.env.action_space.n)

        return np.argmax(self.q_table[state_key])

    def update(self, state, action, reward, next_state):
        state_key = self.get_key(state)
        next_state_key = self.get_key(next_state)

        if state_key not in self.q_table:
            self.q_table[state_key] = np.zeros(self.env.action_space.n)
        if next_state_key not in self.q_table:
            self.q_table[next_state_key] = np.zeros(self.env.action_space.n)

        # Q値の更新
        old_value = self.q_table[state_key][action]
        next_max = np.max(self.q_table[next_state_key])
        new_value = (1 - self.alpha) * old_value + self.alpha * (
            reward + self.gamma * next_max
        )
        self.q_table[state_key][action] = new_value


from tqdm import tqdm


def train():
    env = MazeEnv()
    agent = QLearningAgent(env)
    episodes = 100000

    for episode in tqdm(range(episodes)):
        state = env.reset()
        total_reward = 0
        done = False

        for _ in range(10000):
            action = agent.get_action(state)
            next_state, reward, done, _ = env.step(action)
            agent.update(state, action, reward, next_state)
            state = next_state
            total_reward += reward

        if episode % 100 == 0:
            print(f"Episode: {episode}, Total Reward: {total_reward}")

    return env, agent


# トレーニングの実行
env, agent = train()

# 学習済みエージェントのテスト
state = env.reset()
env.render()
done = False

while not done:
    action = agent.get_action(state)
    state, _, done, _ = env.step(action)
    env.render()
