use proconio::input;

fn main() {
    input! {
        n: usize,
        q: usize,
        t :[i32; q],
    }
    let mut den = vec![true; n];
    for i in 0..q {
        den[t[i] as usize - 1] = !den[t[i] as usize - 1];
    }
    let mut ans = 0;
    for i in 0..n {
        if den[i] {
            ans += 1;
        }
    }
    println!("{}", ans);
}
