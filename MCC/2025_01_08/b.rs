use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars,
    }
    let n = s.len() as i32;
    let mut zero: i32 = 0;
    let mut one: i32 = 0;
    for c in s {
        if c == '0' {
            zero += 1;
        } else {
            one += 1;
        }
    }
    println!("{}", n - (zero - one).abs());
}
