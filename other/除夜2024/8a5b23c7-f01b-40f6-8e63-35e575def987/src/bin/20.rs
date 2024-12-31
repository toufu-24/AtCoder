use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {
        a: i32,
        b: i32,
    }
    let mut set = HashSet::new();
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.remove(&a);
    set.remove(&b);
    if set.len() == 1 {
        println!("{}", set.iter().next().unwrap());
    } else {
        println!("{}", -1);
    }
}
