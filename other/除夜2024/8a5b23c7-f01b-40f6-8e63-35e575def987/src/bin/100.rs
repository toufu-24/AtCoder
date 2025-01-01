use proconio::{input, marker::Chars};
use std::collections::HashSet;

fn main() {
    input! {
        n: usize,
        k: usize,
        a: [usize; n]
    }

    let mut ans = (k + 1) * k / 2;
    let mut set = HashSet::new();
    for i in 0..n {
        if set.contains(&a[i]) {
            continue;
        }
        if a[i] <= k {
            ans -= a[i];
        }
        set.insert(a[i]);
    }
    println!("{}", ans);
}
