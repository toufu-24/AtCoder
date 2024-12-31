use proconio::input;

fn main() {
    input! {
        n: i64
    }
    let mut ans = 0;
    for i in 0..=1_000_000 as i64 {
        if i * i * i <= n {
            let k = i * i * i;
            let k_str = k.to_string();
            let k_str_rev = k_str.chars().rev().collect::<String>();
            let palindrome = k_str == k_str_rev;
            if palindrome {
                ans = ans.max(k);
            }
        }
    }
    println!("{}", ans);
}
