import Control.Applicative
import Control.Monad
import Data.Array
import Data.Bool (bool)
import Data.List (foldl')
import Data.Maybe (fromMaybe)

main :: IO ()
main = do
  -- hとwを読み込む
  [h, w] <- map read . words <$> getLine
  -- h行の迷路を読み込む
  ss <- replicateM h getLine
  -- 答えを出力する
  print $ solve h w ss

-- solve関数: 迷路の高さh、幅w、迷路のデータssを受け取り、最短経路のコストを返す
solve :: Int -> Int -> [String] -> Int
solve h w ss = bfs dist queue 1
  where
    inf = 10 ^ 9 :: Int -- 無限大の代わりとして大きな数を使う
    -- 距離配列を初期化する。全て無限大で埋め、スタート地点(0,0)のみ0にする
    dist = array ((0, 0), (h - 1, w - 1)) [((i, j), inf) | i <- [0 .. h - 1], j <- [0 .. w - 1]] // [((0, 0), 0)]
    queue = [(0, 0)] -- BFSのキュー。スタート地点から始める

    -- bfs関数: 幅優先探索を行い、最短距離を求める
    bfs :: Array (Int, Int) Int -> [(Int, Int)] -> Int -> Int
    bfs dist [] score = if dist ! (h - 1, w - 1) == inf then -1 else score
    -- ゴール地点に到達していない場合、-1を返し到達した場合は現在のスコアを返す
    bfs dist ((i, j) : queue) score = bfs dist' queue' score'
      where
        -- 上下左右の4方向を定義する
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        -- 各方向に対してprocess関数を実行し、dist, queue, scoreを更新する
        (dist', queue', score') = foldl' process (dist, queue, score) directions

        -- process関数: 特定の方向に移動し、更新されたdist, queue, scoreを返す
        process (d, q, s) (di, dj) =
          let (i', j') = (i + di, j + dj) -- 移動先の座標
              inBounds = 0 <= i' && i' < h && 0 <= j' && j' < w -- 範囲内チェック
              isPath = inBounds && ss !! i' !! j' == '.' -- 移動可能な道であるか確認
              newDist = if inBounds then d ! (i, j) + 1 else inf -- 新しいコストを計算
           in if isPath && d ! (i', j') > newDist -- 新しいコストが小さい場合のみ更新
                then (d // [((i', j'), newDist)], q ++ [(i', j')], s + 1) -- 距離配列とキュー、スコアを更新
                else (d, q, s) -- 更新不要ならそのまま返す
