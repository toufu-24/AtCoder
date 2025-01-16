use proconio::input;

fn main() {
    input! {
        n: usize,
        d: usize,
    }
    let mut t = vec![0; n];
    let mut l = vec![0; n];
    for i in 0..n {
        input! {
            ti: usize,
            li: usize,
        }
        t[i] = ti;
        l[i] = li;
    }

    for k in 1..=d {
        let mut ans = 0;
        for i in 0..n {
            let gram = t[i] * (l[i] + k);
            ans = ans.max(gram);
        }
        println!("{}", ans);
    }
}
