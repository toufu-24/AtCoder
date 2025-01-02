use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars,
    }

    for c in s{
        print!("{} ", c);
    }
    println!();
}
