use proconio::{input, marker::Chars};
use std::collections::HashMap;

fn main() {
    input! {
        s: Chars
    }
    let mut cnt = vec![0; 26];
    for c in s {
        cnt[(c as u8 - b'a') as usize] += 1;
    }
    let mut cnt_cnt = HashMap::new();
    for i in 0..26 {
        if cnt[i] == 0 {
            continue;
        }
        *cnt_cnt.entry(cnt[i]).or_insert(0) += 1;
    }

    // for (cnt, cnt_cnt) in cnt_cnt.iter() {
    //     println!("{}:{} ", cnt, cnt_cnt);
    // }
    for &c in cnt_cnt.values() {
        if c != 2 {
            println!("No");
            return;
        }
    }
    println!("Yes");
}
