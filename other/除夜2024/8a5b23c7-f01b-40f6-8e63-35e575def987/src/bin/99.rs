use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        qr: [(usize, usize); n],
        q: usize,
        td: [(usize, usize); q]
    }
    for i in 0..q {
        let mut t = td[i].0;
        let mut d = td[i].1;
        t -= 1;
        let mut q = qr[t].0;
        let mut r = qr[t].1;
        d = d.max(r);
        d += (q - (d - r) % q) % q;
        println!("{}", d);
    }
}
