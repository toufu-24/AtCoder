use proconio::input;
use std::collections::HashMap;

fn main() {
    input! {
        n: usize,
        ac: [(i32, String); n]
    }
    let mut map: HashMap<String, i32> = HashMap::new();
    for (a, c) in ac {
        map.entry(c).and_modify(|e| *e = (*e).min(a)).or_insert(a);
    }
    let mut ans = 0;
    for (_, a) in map {
        ans = ans.max(a);
    }
    println!("{}", ans);
}
