use proconio::{input, marker::Chars};

fn main() {
    input! {
        mut s: Chars
    }
    if s[0].is_uppercase() && s[1..].iter().all(|&c| c.is_lowercase()) {
        println!("Yes");
    } else {
        println!("No");
    }
}
