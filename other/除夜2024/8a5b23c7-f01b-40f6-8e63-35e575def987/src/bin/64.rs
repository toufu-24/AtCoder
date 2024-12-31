use proconio::input;

fn main() {
    input! {
        n: i64,
        t: i64,
        a: i64,
    }
    if t >= n / 2 + (n % 2 == 1) as i64 || a >= n / 2 + (n % 2 == 1) as i64 {
        println!("Yes");
    } else {
        println!("No");
    }
}
