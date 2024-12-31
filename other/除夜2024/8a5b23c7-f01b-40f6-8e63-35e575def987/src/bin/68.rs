use proconio::input;

fn main() {
    input! {
        m: usize,
    }
    // 3進数
    let mut n = m;
    let mut s = vec![];
    while n > 0 {
        s.push(n % 3);
        n /= 3;
    }
    let mut ans = vec![];
    for i in 0..s.len() {
        for _ in 0..s[i] {
            ans.push(i);
        }
    }
    println!("{}", ans.len());
    for i in ans {
        print!("{} ", i);
    }
}
