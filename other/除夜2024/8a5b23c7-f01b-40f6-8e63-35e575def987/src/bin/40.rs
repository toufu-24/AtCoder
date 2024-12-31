use proconio::input;

fn main() {
    input! {
        n: usize,
        mut l: usize,
        mut r: usize
    }
    l -= 1;
    let mut a = vec![0; n];
    for i in 0..n {
        a[i] = i + 1;
    }
    a[l..r].reverse();
    for i in 0..n {
        print!("{} ", a[i]);
    }
}
