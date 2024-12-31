use proconio::input;

fn main() {
    input! {
        n: usize,
        p: [i32; n],
        q: usize,
        ab: [(i32, i32); q]
    }
    for (a, b) in ab {
        for p_i in &p {
            if *p_i == a {
                println!("{}", a);
                break;
            }
            if *p_i == b {
                println!("{}", b);
                break;
            }
        }
    }
}
