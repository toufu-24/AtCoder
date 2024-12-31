use proconio::input;

fn main() {
    input! {
        n: usize,
        t: i32,
        p: i32,
        mut l: [i32; n]
    }
    let mut ans = 0;
    loop {
        let mut cnt = 0;
        for i in 0..l.len() {
            if l[i] >= t {
                cnt += 1;
            }
        }
        if cnt >= p {
            break;
        }
        ans += 1;
        for i in 0..l.len() {
            l[i] += 1;
        }
    }
    println!("{}", ans);
}
