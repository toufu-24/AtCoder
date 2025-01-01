use proconio::{input, marker::Chars};
use std::collections::HashMap;

fn main() {
    input! {
        s: Chars
    }

    let mut ans = true;
    ans &= s.len() % 2 == 0;

    for i in 0..s.len() / 2 {
        ans &= s[i * 2] == s[i * 2 + 1];
    }
    let mut map = HashMap::new();
    for i in s {
        *map.entry(i).or_insert(0) += 1;
    }
    for (_, v) in map {
        ans &= v == 2;
    }

    println!("{}", if ans { "Yes" } else { "No" });
}
