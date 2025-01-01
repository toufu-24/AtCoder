use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        TV: [(i64, i64); n]
    }

    let mut now = 0;
    let mut prev = 0;
    for (t, v) in TV {
        now = (now - (prev - t).abs()).max(0);
        now += v;
        prev = t;
    }
    println!("{}", now);
}
