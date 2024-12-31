use proconio::input;
fn main() {
    input! {
        n: i32,
        k: i32,
        a: [i32; n],
    }
    let low = &a[(n - k) as usize..];
    for i in 0..low.len() {
        print!("{} ", low[i]);
    }
    for i in 0..(n - k - 1) as usize {
        print!("{} ", a[i]);
    }
    println!("{}", a[n as usize - k as usize - 1]);
}
