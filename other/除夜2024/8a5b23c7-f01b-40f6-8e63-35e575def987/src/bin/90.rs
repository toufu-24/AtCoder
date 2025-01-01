use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        s: [String; n]
    }
    let mut sweet = false;
    for i in 0..n - 1 {
        let s_i = &s[i];
        if s_i == "sweet" {
            if sweet {
                println!("No");
                return;
            }
            sweet = true;
        } else {
            sweet = false;
        }
    }
    println!("Yes");
}
