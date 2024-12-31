use proconio::input;

fn main() {
    input! {
        n:usize,
        a: [i64; n],
        w: [i64; n]
    }
    let mut ans = 0;
    let mut maxes = vec![0; n];
    for i in 0..n {
        maxes[a[i] as usize - 1] = maxes[a[i] as usize - 1].max(w[i]);
    }
    let sum = maxes.iter().sum::<i64>();
    let all_sum = w.iter().sum::<i64>();
    ans = all_sum - sum;
    println!("{}", ans);
}
