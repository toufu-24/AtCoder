use proconio::input;

fn main() {
    input! {
        n: usize,
        c: i64,
        t: [i64; n]
    }
    let mut prev = -1_000_000_000;
    let mut ans = 0;
    for i in 0..n {
        if t[i] - prev >= c {
            ans += 1;
            prev = t[i];
        }
    }
    println!("{}", ans);
}
