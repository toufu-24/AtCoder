use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
    }
    for x in 0..=n {
        for y in 0..=n {
            if x + y > n {
                break;
            }
            for z in 0..=n {
                if x + y + z > n {
                    break;
                }
                println!("{} {} {}", x, y, z);
            }
        }
    }
}
