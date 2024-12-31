use proconio::input;

fn main() {
    input! {
        n: usize,
    }
    let mut a = Vec::new();
    let mut b = Vec::new();
    for _ in 0..n {
        input! {
            _a: i64,
            _b: i64,
        }
        a.push(_a);
        b.push(_b);
    }
    let kata = a.iter().sum::<i64>();
    let mut ans = 0;
    for i in 0..n {
        ans = ans.max(kata - a[i] + b[i]);
    }
    println!("{}", ans);
}
