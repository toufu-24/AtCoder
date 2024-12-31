use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {
        s: String,
    }
    let mut set = HashSet::new();
    for i in 0..s.len() {
        let mut tmp = "".to_string();
        for j in i..s.len() {
            tmp.push(s.chars().nth(j).unwrap());
            set.insert(tmp.clone());
        }
    }
    println!("{}", set.len());
}
