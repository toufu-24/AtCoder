use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        d: i64,
        mut s: Chars
    }
    let mut cnt = 0;
    for i in (0..n).rev() {
        if s[i] == '@' && cnt < d {
            cnt += 1;
            s[i] = '.';
        }
    }
    println!("{}", s.iter().collect::<String>());
}
