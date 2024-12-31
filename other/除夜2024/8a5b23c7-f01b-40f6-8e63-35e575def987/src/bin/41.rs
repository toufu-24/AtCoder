use proconio::input;

fn main() {
    input! {
        n: usize,
        m: i32,
        h: [i32; n],
    }
    let mut remain = m;
    for i in 0..n {
        let h_i = h[i];
        if h_i <= remain {
            remain -= h_i;
        } else {
            print!("{}", i);
            return;
        }
    }
    println!("{}", n);
}
