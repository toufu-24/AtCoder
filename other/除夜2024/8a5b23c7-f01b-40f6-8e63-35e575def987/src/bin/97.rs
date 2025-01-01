use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        x: i64,
        y: i64,
        mut a: [i64; n],
        mut b: [i64; n]
    }
    a.sort();
    b.sort();
    a = a.into_iter().rev().collect();
    b = b.into_iter().rev().collect();
    let mut sweet = 0;
    let mut solty = 0;
    for i in 0..n {
        sweet += a[i];
        solty += b[i];
        if sweet > x || solty > y {
            println!("{}", i + 1);
            return;
        }
    }
    println!("{}", n);
}
