use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
    }
    let mut a = vec![vec![]; n];
    for i in 0..n {
        input! {
            l: [i64; i+1]
        }
        a[i] = l;
    }

    let mut now = 1;
    for i in 0..n {
        let low = now.min(i + 1);
        let high = now.max(i + 1);
        now = a[high - 1][low - 1] as usize;
    }
    println!("{}", now);
}
