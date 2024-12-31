use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        d: i32,
        s: Chars
    }
    let mut cnt = 0;
    for i in 0..n {
        if s[i] == '@' {
            cnt += 1;
        }
    }
    cnt = n as i32 - cnt;
    let ans = 0.max(cnt + d);
    println!("{}", ans);
}
