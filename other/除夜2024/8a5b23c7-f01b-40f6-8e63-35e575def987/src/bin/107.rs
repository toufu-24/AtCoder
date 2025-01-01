use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        mut a: [i64; n],
    }

    let mut s = vec![0; n];
    let mut t = vec![0; n];
    for i in 0..n - 1 {
        input! {
            tmp: i64,
            tmp2: i64
        }
        s[i] = tmp;
        t[i] = tmp2;
    }

    for i in 0..n - 1 {
        a[i + 1] += a[i] / s[i] * t[i];
    }
    println!("{}", a[n - 1]);
}
