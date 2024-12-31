use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars
    }
    let mut idx = 0;
    let mut i = 0;
    let mut ans = true;
    while i < s.len() {
        if (s[i] as u8) == ('A' as u8 + idx) {
            i += 1;
        } else {
            idx += 1;
            if idx == 3 {
                ans = false;
                break;
            }
        }
    }
    if ans {
        println!("Yes");
    } else {
        println!("No");
    }
}
