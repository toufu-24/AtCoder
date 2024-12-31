use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars
    }
    let mut v = vec![0; 26];
    for c in s {
        v[(c as u8 - b'a') as usize] += 1;
    }
    let max_val = v.iter().max().unwrap();
    for i in 0..26 {
        if v[i] == *max_val {
            println!("{}", (i as u8 + b'a') as char);
            return;
        }
    }
}
