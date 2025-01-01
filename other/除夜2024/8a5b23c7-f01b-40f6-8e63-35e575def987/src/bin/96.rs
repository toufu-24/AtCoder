use proconio::{input, marker::Chars};

fn main() {
    input! {
        q: usize,
    }
    let mut arr = vec![];
    for _ in 0..q {
        input! {
            t: i64,
        }
        if t == 1 {
            input! {
                x: i64,
            }
            arr.push(x);
        } else {
            input! {
                k: usize,
            }
            println!("{}", arr[arr.len() - k]);
        }
    }
}
