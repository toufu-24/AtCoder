use proconio::{input, marker::Chars};
use std::collections::HashSet;

fn main() {
    input! {
        n: usize,
        s: Chars
    }

    let mut ans = true;
    ans &= s.len() % 2 == 1;
    for i in 0..(s.len()) / 2 {
        ans &= s[i] == '1';
    }
    ans &= s[s.len() / 2] == '/';
    for i in (s.len() / 2 + 1)..s.len() {
        ans &= s[i] == '2';
    }
    println!("{}", if ans { "Yes" } else { "No" });
}
