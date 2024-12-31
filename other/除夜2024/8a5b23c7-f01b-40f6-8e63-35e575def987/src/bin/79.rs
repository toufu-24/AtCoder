use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        mut a: [i64; n]
    }
    a.sort();
    let mut ans = 1_000_000_000_000_000_000 as i64;
    for i in 0..=k {
        let l = a[i];
        let r = a[n - k + i - 1];
        ans = ans.min(r - l);
    }
    println!("{}", ans);
}
