use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {
        n: usize,
        m: usize,
        s: [String; n],
        t: [String; m],
    }

    let mut set = HashSet::new();
    for t_i in t {
        set.insert(t_i);
    }

    for s_i in s {
        if set.contains(&s_i) {
            println!("Yes");
        } else {
            println!("No");
        }
    }
}
