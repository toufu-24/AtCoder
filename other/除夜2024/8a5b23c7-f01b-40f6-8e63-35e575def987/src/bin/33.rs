use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; n]
    }
    let mut tmp = 0;
    let mut min_tmp = 1_000_000_000_000_000_000;
    for i in 0..n {
        tmp += a[i];
        min_tmp = min_tmp.min(tmp);
    }
    println!("{}", tmp - min_tmp.min(0));
}
