use proconio::input;

fn main() {
    input! {
        a: i32,
        b: i32
    }
    if a == b {
        println!("1");
    } else if a % 2 != b % 2 {
        println!("2");
    } else {
        println!("3");
    }
}
