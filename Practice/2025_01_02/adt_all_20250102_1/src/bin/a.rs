use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        s: Chars,
        t: Chars,
    }
    let mut flag = true;
    for i in 0..n {
        if s[i] != t[i] {
            if (s[i] == 'l' && t[i] == '1')
                || (s[i] == 'o' && t[i] == '0')
                || (s[i] == '1' && t[i] == 'l')
                || (s[i] == '0' && t[i] == 'o')
            {
            } else {
                flag = false;
                break;
            }
        }
    }

    println!("{}", if flag { "Yes" } else { "No" });
}
