use proconio::{input, marker::Chars};

fn main() {
    input! {
        mut s: Chars
    }
    let upper_cnt = s.iter().filter(|&c| c.is_uppercase()).count();
    let lower_cnt = s.iter().filter(|&c| c.is_lowercase()).count();
    if upper_cnt < lower_cnt {
        for i in 0..s.len() {
            s[i] = s[i].to_lowercase().next().unwrap();
        }
    } else {
        for i in 0..s.len() {
            s[i] = s[i].to_uppercase().next().unwrap();
        }
    }
    println!("{}", s.iter().collect::<String>());
}
