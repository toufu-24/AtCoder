use proconio::input;

fn ctz(n: i32) -> i32 {
    let mut count = 0;
    let mut n = n;
    while n & 1 == 0 {
        n >>= 1;
        count += 1;
    }
    count
}

fn main() {
    input! {
        n: i32
    }
    println!("{}", ctz(n));
}
