use proconio::{input, marker::Chars};

fn main() {
    input! {
        w: usize,
        b: usize
    }

    let s = "wbwbwwbwbwbw";
    let n = w + b;
    let s_many = s.repeat(25);
    let mut found = false;
    for i in 0..=s_many.len().saturating_sub(n) {
        let slice = &s_many[i..i + n];
        if slice.matches('w').count() == w && slice.matches('b').count() == b {
            found = true;
            break;
        }
    }
    println!("{}", if found { "Yes" } else { "No" });
}
