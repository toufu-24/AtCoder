use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        m: usize,
        s: [Chars; n],
    }

    let mut ans = n;
    for i in 0..1 << n {
        let mut cnt = 0;
        let mut check = vec![false; m];
        for j in 0..n {
            if i >> j & 1 == 1 {
                cnt += 1;
                for k in 0..m {
                    if s[j][k] == 'o' {
                        check[k] = true;
                    }
                }
            }
        }
        if check.iter().all(|&x| x) {
            ans = ans.min(cnt);
        }
    }
    println!("{}", ans);
}
