use proconio::{input, marker::Chars};

fn main() {
    input! {
        mut s: Chars
    }
    s.sort();
    if s == "ABC".chars().collect::<Vec<char>>() {
        println!("Yes");
    } else {
        println!("No");
    }
}
