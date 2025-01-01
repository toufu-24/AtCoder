use proconio::{input, marker::Chars};
use std::collections::HashSet;

fn main() {
    input! {
        n: usize,
        m: usize,
        ab: [(usize, String); m]
    }

    let mut set = HashSet::new();
    for i in 0..m {
        if ab[i].1 == "M" && !set.contains(&ab[i].0) {
            set.insert(ab[i].0);
            println!("Yes");
        } else {
            println!("No");
        }
    }
}
