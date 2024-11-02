import numpy as np
from collections import Counter


def count_subarrays_with_mod_sum_fft_continuous(A, M):
    # 累積和のモジュロを計算
    cumulative_sum = 0
    mods = [0]  # 初期値0を追加（和が0の部分配列を含む）
    for a in A:
        cumulative_sum += a
        mods.append(cumulative_sum % M)

    # 剰余の出現回数をカウント
    mod_counts = Counter(mods)

    # 剰余のカウントを配列に変換
    freq = np.zeros(M, dtype=np.int64)
    for mod, count in mod_counts.items():
        freq[mod] = count

    # FFTによる畳み込み
    fft_freq = np.fft.fft(freq)
    fft_result = fft_freq * fft_freq
    result = np.fft.ifft(fft_result).real.round().astype(int)  # 実数部を整数に

    # 各剰余ごとの組み合わせ数を抽出
    counts = result[:M] // 2  # 各カウントは2回カウントされているため2で割る

    # 自分自身との組み合わせをカウント
    for mod, count in mod_counts.items():
        counts[mod] += count * (count - 1) // 2

    return counts


N, M = map(int, input().split())
A = list(map(int, input().split()))

result = count_subarrays_with_mod_sum_fft_continuous(A, M)
print(result)  # 各 mod の和が i になる部分配列の個数
ans = 0
for i in range(M):
    ans += result[i] * i
print(ans)  # mod の和が M の倍数になる部分配列の個数
