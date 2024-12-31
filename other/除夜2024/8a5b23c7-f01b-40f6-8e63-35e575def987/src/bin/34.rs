use proconio::input;

fn main() {
    input! {
        n: usize
    }
    if n == 1 {
        println!("0");
        return;
    }
    // 5進数で表現する
    let mut n_five = n - 1;
    let mut ans = String::new();
    while n_five > 0 {
        let r = n_five % 5;
        ans.push_str(&(r * 2).to_string());
        n_five /= 5;
    }
    let ans = ans.chars().rev().collect::<String>();
    println!("{}", ans);
}
