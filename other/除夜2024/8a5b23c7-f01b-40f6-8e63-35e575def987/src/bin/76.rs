use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        a: [i32; n]
    }
    let mut aki = k;
    let mut ans = 0;
    let mut idx = 0;
    loop {
        if aki < a[idx] as usize {
            aki = k;
            ans += 1;
        } else {
            aki -= a[idx] as usize;
            idx += 1;
            if idx == n {
                ans += 1;
                break;
            }
        }
    }
    println!("{}", ans);
}
