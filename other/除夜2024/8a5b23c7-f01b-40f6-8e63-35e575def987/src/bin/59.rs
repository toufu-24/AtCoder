use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars
    }
    if s[0] == '<' && s[s.len() - 1] == '>' {
        let mut flag = true;
        for i in 1..s.len() - 1 {
            if s[i] == '=' {
                continue;
            } else {
                flag = false;
                break;
            }
        }
        if flag {
            println!("Yes");
        } else {
            println!("No");
        }
    } else {
        println!("No");
    }
}
