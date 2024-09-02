import torch
import torch.nn as nn
import torch.optim as optim
import numpy as np
from collections import deque
import random


# 環境の定義
class SignalControlEnv:
    def __init__(self, A, paths, lb):
        self.A = A
        self.paths = paths
        self.lb = lb
        self.la = len(A)
        self.t = len(paths)
        self.reset()

    def reset(self):
        self.current_time = 0
        self.B = [-1] * self.lb
        self.score = 0
        return self._get_state()

    def step(self, action):
        # actionを使って信号操作を決定
        if action == 1:  # 信号操作を行う
            a_idx = min(max(0, self.current_time), self.la - self.lb)
            for k in range(self.lb):
                self.B[k] = self.A[a_idx + k]
            reward = -1  # 信号操作にはコストがかかる
        else:
            reward = 0

        path = self.paths[self.current_time]
        for node in path:
            if node not in self.B:
                reward -= 10  # ペナルティ

        self.current_time += 1
        done = self.current_time == self.t - 1
        return self._get_state(), reward, done

    # SignalControlEnv クラスの _get_state メソッド
    def _get_state(self):
        return self.B + self.paths[self.current_time]


# DQNエージェントの定義
class DQNAgent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.action_size = action_size
        self.memory = deque(maxlen=2000)
        self.gamma = 0.95
        self.epsilon = 1.0
        self.epsilon_min = 0.01
        self.epsilon_decay = 0.995
        self.model = self._build_model()

    def _build_model(self):
        model = nn.Sequential(
            nn.Linear(self.state_size, 24),
            nn.ReLU(),
            nn.Linear(24, 24),
            nn.ReLU(),
            nn.Linear(24, self.action_size),
        )
        return model

    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def act(self, state):
        if np.random.rand() <= self.epsilon:
            return random.randrange(self.action_size)
        state = torch.FloatTensor(state).unsqueeze(0)
        act_values = self.model(state)
        return np.argmax(act_values.detach().numpy())

    def replay(self, batch_size):
        minibatch = random.sample(self.memory, batch_size)
        for state, action, reward, next_state, done in minibatch:
            state = torch.FloatTensor(state)
            next_state = torch.FloatTensor(next_state)
            target = reward
            if not done:
                target = reward + self.gamma * np.amax(
                    self.model(next_state).detach().numpy()
                )
            target_f = self.model(state)
            target_f[0][action] = target
            loss = nn.MSELoss()(self.model(state), target_f)
            optimizer = optim.Adam(self.model.parameters())
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay


# メイン学習ループ
def train_agent(env, episodes=1000):
    state_size = env.lb + len(env.paths[0])
    action_size = 2  # 信号操作を行うか行わないか
    agent = DQNAgent(state_size, action_size)
    batch_size = 32

    for e in range(episodes):
        state = env.reset()
        total_reward = 0
        for time in range(env.t - 1):
            action = agent.act(state)
            next_state, reward, done = env.step(action)
            agent.remember(state, action, reward, next_state, done)
            state = next_state
            total_reward += reward
            if done:
                print(
                    f"episode: {e}/{episodes}, score: {env.score}, total_reward: {total_reward}, epsilon: {agent.epsilon:.2}"
                )
                break
            if len(agent.memory) > batch_size:
                agent.replay(batch_size)

    return agent


# 学習済みエージェントを使用して最適な信号操作を生成
def generate_optimal_actions(env, agent):
    state = env.reset()
    actions = []
    for _ in range(env.t - 1):
        action = agent.act(state)
        actions.append(action)
        state, _, done = env.step(action)
        if done:
            break
    return actions


# メイン関数の修正
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

    # 環境の初期化
    env = SignalControlEnv(A, paths, lb)

    # エージェントの学習
    trained_agent = train_agent(env)

    # 最適な信号操作の生成
    optimal_actions = generate_optimal_actions(env, trained_agent)

    # 結果の出力
    print(" ".join(map(str, A)))
    for i, action in enumerate(optimal_actions):
        if action == 1:
            a_idx = min(max(0, i), la - lb)
            print(f"s {lb} {a_idx} 0")
        path = paths[i]
        for node in path:
            print(f"m {node}")


if __name__ == "__main__":
    main()
