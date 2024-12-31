use proconio::input;

fn main() {
    input! {
        n: usize,
        h: [i32; n]
    }
    for (i, &h_i) in h.iter().enumerate() {
        if h_i > h[0] {
            println!("{}", i + 1);
            return;
        }
    }
    println!("{}", -1);
}
