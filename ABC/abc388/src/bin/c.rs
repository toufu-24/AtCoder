use proconio::input;
use superslice::Ext;

fn main() {
    input! {
        n: usize,
    mut a: [usize; n],
    }
    a.sort();

    let mut ans = 0;
    for ai in a.iter() {
        let a2 = ai * 2;
        let idx = a.lower_bound(&a2);
        ans += n - idx;
    }
    println!("{}", ans);
}
