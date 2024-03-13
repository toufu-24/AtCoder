import numpy as np

import matplotlib.pyplot as plt

# nの範囲を設定
n = np.linspace(0, 5, 400)

# 2^nとn^2の計算
y1 = 2**n
y2 = n**2

# グラフの描画
plt.figure(figsize=(10, 6))
plt.plot(n, y1, label='2^n')
plt.plot(n, y2, label='n^2')
plt.legend()

# グラフの表示
plt.show()