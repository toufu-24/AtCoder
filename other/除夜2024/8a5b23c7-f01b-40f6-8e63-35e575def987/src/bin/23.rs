use proconio::input;
use std::collections::HashMap;

fn main() {
    input! {
        s: String
    }
    let mut map = HashMap::new();
    for c in s.chars() {
        *map.entry(c).or_insert(0) += 1;
    }
    let mut c = 'a';
    for (ch, cnt) in map {
        if cnt == 1 {
            c = ch;
        }
    }

    let s_chars: Vec<char> = s.chars().collect();
    for i in 0..s_chars.len() {
        if s_chars[i] == c {
            println!("{}", i + 1);
            return;
        }
    }
}
