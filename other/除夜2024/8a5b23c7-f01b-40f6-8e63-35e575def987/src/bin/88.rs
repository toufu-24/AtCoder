use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        xy: [(i64, i64); n]
    }

    for i in 0..n {
        let mut max_val = 0;
        let mut max_idx = 0;
        for j in 0..n {
            if i == j {
                continue;
            }
            let val = (xy[i].0 - xy[j].0) * (xy[i].0 - xy[j].0)
                + (xy[i].1 - xy[j].1) * (xy[i].1 - xy[j].1);
            if val > max_val {
                max_val = val;
                max_idx = j;
            }
        }
        println!("{}", max_idx + 1);
    }
}
