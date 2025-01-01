use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        k: usize,
        mut s: Chars
    }

    let kth_idx;
    if s[0] == '1' {
        kth_idx = k * 2 - 2;
    } else {
        kth_idx = k * 2 - 1;
    }

    let mut s_split = Vec::new();
    let mut now_str = s[0].to_string();
    for i in 1..s.len() {
        if s[i] != s[i - 1] {
            s_split.push(now_str);
            now_str = s[i].to_string();
        } else {
            now_str.push(s[i]);
        }
    }
    s_split.push(now_str);

    // print!("s_split: ");
    // for s_i in 0..s_split.len() {
    //     print!("{} ", s_split[s_i]);
    // }
    // println!();
    // kth_idx と kth_idx - 1 の要素をswap
    for i in 0..s_split.len() {
        if i == kth_idx {
            print!("{}", s_split[kth_idx - 1]);
        } else if i == kth_idx - 1 {
            print!("{}", s_split[kth_idx]);
        } else {
            print!("{}", s_split[i]);
        }
    }
    println!();
}
