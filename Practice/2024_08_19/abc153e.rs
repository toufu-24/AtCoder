use proconio::input;

fn main() {
    input! {
        h: usize,
        n: usize,
        ab : [(i64, i64); n],
    }

    const INF: i64 = 10_i64.pow(18);
    // dp[i][j] := i番目までの魔法を使って，体力がjとなるような最小の魔力
    // let mut dp = vec![vec![INF; h + 1]; n];
    // for i in 0..n {
    //     dp[i][h] = 0;
    // }

    // for i in 1..n {
    //     dp[i] = dp[i - 1].clone();
    //     for j in (0..=h).rev() {
    //         if j >= ab[i - 1].0 as usize {
    //             dp[i][j - ab[i - 1].0 as usize] =
    //                 (dp[i - 1][j] + ab[i - 1].1).min(dp[i][j - ab[i - 1].0 as usize]);
    //         } else if j as i64 - ab[i - 1].0 < 0 {
    //             dp[i][0] = (dp[i - 1][j] + ab[i - 1].1).min(dp[i - 1][0]);
    //         }
    //     }
    // }

    // dp[i] := 体力がiとなるような最小の魔力
    let mut dp = vec![INF; h + 1];
    dp[h] = 0;
    for i in 0..n {
        for j in (0..=h).rev() {
            if j >= ab[i].0 as usize {
                dp[j - ab[i].0 as usize] = (dp[j] + ab[i].1).min(dp[j - ab[i].0 as usize]);
            } else if j as i64 - ab[i].0 < 0 {
                dp[0] = (dp[j] + ab[i].1).min(dp[0]);
            }
        }
    }

    println!("{}", dp[0]);
}
