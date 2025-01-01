use proconio::{input, marker::Chars};
use std::collections::HashMap;

fn main() {
    input! {
        n: usize,
        a: [i64; n]
    }
    let mut map: HashMap<i64, usize> = HashMap::new();
    for i in 0..n {
        if !map.contains_key(&a[i]) {
            println!("-1");
        } else {
            println!("{}", map[&a[i]] + 1);
        }
        map.insert(a[i], i);
    }
}
