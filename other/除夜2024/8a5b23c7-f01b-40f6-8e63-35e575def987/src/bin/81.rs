use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
    mut s: [Chars; n]
    }

    let mut now_max = 0;
    for i in 0..n {
        now_max = now_max.max(s[i].len());
        if s[i].len() < now_max {
            s[i].resize(now_max, '*');
        }
    }

    for i in 0..now_max {
        for j in (0..n).rev() {
            if i >= s[j].len() {
                continue;
            }
            print!("{}", s[j][i]);
        }
        println!();
    }
}
