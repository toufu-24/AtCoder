use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars,
    }
    let mut rice = false;
    for i in 0..s.len() {
        if s[i] == 'R' {
            rice = true;
        }
        if s[i] == 'M' {
            if rice {
                println!("Yes");
                return;
            } else {
                println!("No");
                return;
            }
        }
    }
}
