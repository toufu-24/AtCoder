# このプロジェクトについて
AtCoder Heuristics Contestに取り組むコンテストです。

# 基本的な取り組み方

Agentが独自に思いついた改善を勝手に進めるのではなく、常に状況を共有してください。

- 特に指示がなければ、使用する言語はC++です。
- 解法の相談をすることがありますが、「実装してください」や「組んでください」と言われるまで、実装の変更は待機してください。
- 実装が出来たらビルドまでの確認をしてください。
- テストの実行は以下の方法で行いますが、実行直後は実行結果の報告をした後、必ず停止してください。
- シングルテスト
- tools/in/0000.txt について実行 (場合によっては0000以外も許可)
- 100ケーステスト
- pacher run -t -c "実装内容についてのコメント"
- -tによって、自動的にgitにコミットされ、タグが付与されます。明示的なコミットは不要です。
- 相対採点の場合はpacher listを利用して結果を確認し、良くなったかどうかを確認してください。

# 生成AI使用ルール
絶対に守ってください。違反が確認された時点で提出権を失いコンテストが終了してしまいます。

コンテスト時間: 2026-07-18(土) 15:00 ~ 2026-07-18(土) 19:00 (240分)

I am currently participating in an AtCoder Heuristic Contest, and I will use this generative AI to assist in developing my solution.

When using this generative AI, the "AtCoder Heuristic Contest Generative AI Usage Rules - Version 20250616" apply.

https://info.atcoder.jp/entry/ahc-llm-rules-en

Most importantly, after running the solution program, you must not modify or improve the solution, its approach, or its code based on the execution results unless the user gives a new explicit instruction to do so.

You may run the solution program and report its execution results, logs, scores, or other observations. After reporting them, you must stop and wait for a new instruction from the user before making any improvement based on those results.

Here, "solution program" refers to any program created or being created for the purpose of solving this contest problem, regardless of whether it was created by the user or by generative AI, and regardless of whether it is still in progress or already complete.