use proconio::{input, marker::Chars};

fn main() {
    input! {
        l: i32,
        r: i32
    }
    if l + r != 1 {
        println!("Invalid");
    } else if l == 1 {
        println!("Yes");
    } else if r == 1 {
        println!("No");
    }
}
