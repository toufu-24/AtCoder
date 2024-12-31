use proconio::input;

fn main() {
    input! {
        mut a: i32,
        b: i32,
        d: i32
    }
    loop {
        if a > b {
            break;
        }
        print!("{} ", a);
        a += d;
    }
    println!();
}
