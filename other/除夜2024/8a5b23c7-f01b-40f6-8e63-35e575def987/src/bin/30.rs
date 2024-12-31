use proconio::{input, marker::Chars};

fn main() {
    input! {
            s: [Chars; 12]
    }
    let mut ans = 0;
    for i in 0..12 {
        if i + 1 == s[i].len() {
            ans += 1;
        }
    }
    println!("{}", ans);
}
