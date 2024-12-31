use proconio::input;

fn main() {
    input! {
        n: usize,
        a: i32,
        t: [i32; n]
    }
    let mut now = 0;
    for i in 0..n {
        now = now.max(t[i]);
        now += a;
        println!("{}", now);
    }
}
