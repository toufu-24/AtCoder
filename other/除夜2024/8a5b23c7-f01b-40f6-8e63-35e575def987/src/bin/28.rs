use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars,
        t: Chars
    }
    if s == t {
        println!("0");
        return;
    }
    let n = s.len().min(t.len());
    let mut ans = 0;
    for i in 0..n {
        if s[i] == t[i] {
            ans += 1;
        } else {
            break;
        }
    }
    println!("{}", ans + 1);
}
