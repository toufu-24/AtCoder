import gymnasium as gym
from stable_baselines3 import PPO
from stable_baselines3.common.vec_env import DummyVecEnv

# 環境の作成とVecEnvでラップ
env = DummyVecEnv([lambda: gym.make("CartPole-v1", render_mode="human")])
# PPOモデルの初期化
model = PPO("MlpPolicy", env, verbose=1)

# モデルのトレーニング
model.learn(total_timesteps=10000)

# モデルの保存
model.save("ppo_cartpole")

# 学習済みモデルで環境を評価
obs = env.reset()
for _ in range(1000):
    action, _states = model.predict(obs, deterministic=True)
    obs, reward, done, info = env.step(action)
    env.render()
    if done:
        obs = env.reset()

# 環境を閉じる
env.close()
