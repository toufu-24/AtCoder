use proconio::input;

fn main() {
    input! {
        n: usize,
        k: [i64; n]
    }
    let mut ans = 1_000_000_000_000_000_000 as i64;
    for i in 0..1i64 << n {
        let mut a: i64 = 0;
        let mut b: i64 = 0;
        for j in 0..n {
            if i >> j & 1 == 1 {
                a += k[j];
            } else {
                b += k[j];
            }
        }
        ans = ans.min(a.max(b));
    }
    println!("{}", ans);
}
