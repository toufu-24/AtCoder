use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
    }
    let sz = 3usize.pow(n as u32);
    for r in 0..sz {
        for c in 0..sz {
            let (mut x, mut y) = (r, c);
            let mut white = false;
            while x > 0 || y > 0 {
                if x % 3 == 1 && y % 3 == 1 {
                    white = true;
                    break;
                }
                x /= 3;
                y /= 3;
            }
            print!("{}", if white { '.' } else { '#' });
        }
        println!();
    }
}
