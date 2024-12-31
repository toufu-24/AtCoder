use proconio::input;

fn main() {
    input! {
        n: usize,
        k: i32,
        a: [i32; n]
    }

    for a_i in a {
        if a_i % k == 0 {
            println!("{}", a_i / k);
        }
    }
}
