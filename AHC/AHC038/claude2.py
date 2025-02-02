import numpy as np
import gym
from gym import spaces
import random
from collections import deque


class TakoyakiEnv(gym.Env):
    def __init__(self, N, M, V, initial_state, goal_state):
        super(TakoyakiEnv, self).__init__()

        self.N = N
        self.M = M
        self.V = V
        self.initial_state = np.array([list(map(int, row)) for row in initial_state])
        self.goal_state = np.array([list(map(int, row)) for row in goal_state])

        # ロボットアームの構造を定義
        self.robot_structure = self._design_robot()

        # アクション空間の定義
        # 移動（上下左右）、回転（各関節ごとに時計回り/反時計回り）、掴む/離す
        self.action_space = spaces.MultiDiscrete([5] + [3] * (V - 1) + [2] * V)

        # 観測空間の定義
        # グリッド状態、ロボットアームの位置と姿勢、掴んでいるたこ焼きの状態
        self.observation_space = spaces.Dict(
            {
                "grid": spaces.Box(low=0, high=1, shape=(N, N), dtype=np.int8),
                "robot_state": spaces.Box(
                    low=0, high=N - 1, shape=(V, 2), dtype=np.int8
                ),
                "gripped": spaces.MultiBinary(V),
            }
        )

        self.state = self._get_initial_state()

    def _design_robot(self):
        # シンプルな木構造のロボットを設計
        robot = []
        robot = [(0, 1)]
        return robot

    def _get_initial_state(self):
        # 初期状態を設定
        robot_state = np.zeros((self.V, 2), dtype=np.int8)
        gripped = np.zeros(self.V, dtype=np.int8)
        return {
            "grid": self.initial_state.copy(),
            "robot_state": robot_state,
            "gripped": gripped,
        }

    def reset(self):
        self.state = self._get_initial_state()
        return self.state

    def step(self, action):
        # アクションの実行
        move, rotations, grips = self._parse_action(action)

        # 移動の処理
        self._move_robot(move)

        # 回転の処理
        for joint, rotation in enumerate(rotations):
            if rotation != 0:
                self._rotate_joint(joint, rotation)

        # 掴む/離すの処理
        for tip, grip in enumerate(grips):
            if grip == 1:
                self._toggle_grip(tip)

        # 報酬の計算
        reward = self._calculate_reward()

        # 終了判定
        done = np.array_equal(self.state["grid"], self.goal_state)

        return self.state, reward, done, {}

    def _parse_action(self, action):
        move = action[0]
        rotations = action[1 : self.V]
        grips = action[self.V :]
        return move, rotations, grips

    def _move_robot(self, move):
        if move == 0:  # 上
            if self.state["robot_state"][0][0] > 0:
                self.state["robot_state"][:, 0] -= 1
        elif move == 1:  # 下
            if self.state["robot_state"][0][0] < self.N - 1:
                self.state["robot_state"][:, 0] += 1
        elif move == 2:  # 左
            if self.state["robot_state"][0][1] > 0:
                self.state["robot_state"][:, 1] -= 1
        elif move == 3:  # 右
            if self.state["robot_state"][0][1] < self.N - 1:
                self.state["robot_state"][:, 1] += 1

    def _rotate_joint(self, joint, rotation):
        # 関節を中心とした回転の処理
        # 実装の簡略化のため、90度回転のみを考慮
        pass

    def _toggle_grip(self, tip):
        pos = tuple(self.state["robot_state"][tip])
        if self.state["gripped"][tip] == 0 and self.state["grid"][pos] == 1:
            self.state["gripped"][tip] = 1
            self.state["grid"][pos] = 0
        elif self.state["gripped"][tip] == 1:
            if self.state["grid"][pos] == 0:
                self.state["gripped"][tip] = 0
                self.state["grid"][pos] = 1

    def _calculate_reward(self):
        # 目標状態との一致度に基づく報酬
        matching = np.sum(self.state["grid"] == self.goal_state)
        return matching - (self.N * self.N)


class DQNAgent:
    def __init__(self, env):
        self.env = env
        self.memory = deque(maxlen=2000)
        self.gamma = 0.95  # 割引率
        self.epsilon = 1.0  # 探索率
        self.epsilon_min = 0.01
        self.epsilon_decay = 0.995
        self.learning_rate = 0.001
        self.model = self._build_model()

    def _build_model(self):
        # ニューラルネットワークの構築（実装の簡略化のため省略）
        pass

    def act(self, state):
        if np.random.rand() <= self.epsilon:
            return self.env.action_space.sample()
        # モデルによる行動選択（実装の簡略化のため省略）
        return self.env.action_space.sample()

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def replay(self, batch_size):
        # 経験再生による学習（実装の簡略化のため省略）
        pass


from tqdm import tqdm
def solve_takoyaki_problem(N, M, V, initial_state, goal_state):
    env = TakoyakiEnv(N, M, V, initial_state, goal_state)
    agent = DQNAgent(env)

    episodes = 100
    batch_size = 32

    for e in tqdm(range(episodes)):
        state = env.reset()
        for time in range(10000):
            action = agent.act(state)
            next_state, reward, done, _ = env.step(action)
            agent.remember(state, action, reward, next_state, done)
            state = next_state

            if len(agent.memory) > batch_size:
                agent.replay(batch_size)

            if done:
                break

        if agent.epsilon > agent.epsilon_min:
            agent.epsilon *= agent.epsilon_decay

    return env.robot_structure, agent


# メイン処理
def main():
    # 入力の読み込み
    N, M, V = map(int, input().split())
    V = 1
    initial_state = [input() for _ in range(N)]
    goal_state = [input() for _ in range(N)]

    # 問題を解く
    robot_structure, agent = solve_takoyaki_problem(N, M, V, initial_state, goal_state)

    # ロボット構造の出力
    print(len(robot_structure) + 1)
    for parent, length in robot_structure:
        print(f"{parent} {length}")
    print("0 0")  # 初期位置

    # 操作手順の生成と出力
    state = agent.env.reset()
    done = False
    moves = []
    while not done:
        action = agent.act(state)
        next_state, _, done, _ = agent.env.step(action)
        moves.append(action_to_string(action, V))
        state = next_state
        if len(moves) >= 100000:
            break

    for move in moves:
        print(move)


def action_to_string(action, V):
    # アクションを文字列に変換
    move_chars = [".", "U", "D", "L", "R"]
    rotation_chars = [".", "L", "R"]
    grip_chars = [".", "P"]

    move = move_chars[action[0]]
    rotations = "".join(rotation_chars[r] for r in action[1:V])
    grips = "".join(grip_chars[g] for g in action[V:])

    return move + rotations + grips


if __name__ == "__main__":
    main()
