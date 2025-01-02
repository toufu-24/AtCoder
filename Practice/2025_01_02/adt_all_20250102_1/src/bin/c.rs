use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        k: usize,
        mut s: Chars,
    }

    let mut ans = 0;
    for i in 0..=n - k {
        let mut flag = true;
        for j in 0..k {
            if s[i + j] != 'O' {
                flag = false;
                break;
            }
        }
        if flag {
            ans += 1;
            for j in 0..k {
                s[i + j] = 'X';
            }
        }
    }
    println!("{}", ans);
}
