use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i32; 2*n],
    }
    let mut ans = 0;
    for i in 0..2 * n - 2 {
        if a[i] == a[i + 2] {
            ans += 1;
        }
    }
    println!("{}", ans);
}
