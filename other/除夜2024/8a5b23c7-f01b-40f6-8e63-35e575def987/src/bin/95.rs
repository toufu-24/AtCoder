use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        m: usize,
        a: [i64; m],
        x: [[i64; m]; n]
    }
    let mut arr = vec![0; m];
    for i in 0..n {
        for j in 0..m {
            arr[j] += x[i][j];
        }
    }

    if (0..m).all(|j| arr[j] >= a[j]) {
        println!("Yes");
    } else {
        println!("No");
    }
}
