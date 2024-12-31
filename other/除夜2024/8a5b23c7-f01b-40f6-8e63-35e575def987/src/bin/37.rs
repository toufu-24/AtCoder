use nalgebra::min;
use proconio::input;

fn main() {
    input! {
        r: i32,
        g: i32,
        b: i32,
        c: String
    }
    let mut ans = 0;
    if c == "Red" {
        ans = min(g, b);
    }
    if c == "Green" {
        ans = r.min(b);
    }
    if c == "Blue" {
        ans = r.min(g);
    }
    println!("{}", ans);
}
