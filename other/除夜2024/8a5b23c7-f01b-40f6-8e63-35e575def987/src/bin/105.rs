use proconio::{input, marker::Chars};

fn main() {
    input! {
        x1: i64,
        y1: i64,
        z1: i64,
        x2: i64,
        y2: i64,
        z2: i64,
        x3: i64,
        y3: i64,
        z3: i64,
        x4: i64,
        y4: i64,
        z4: i64
    }

    fn cross(l1: i64, r1: i64, l2: i64, r2: i64) -> bool {
        !(r1 <= l2 || l1 >= r2)
    }

    if cross(x1, x2, x3, x4) && cross(y1, y2, y3, y4) && cross(z1, z2, z3, z4) {
        println!("Yes");
    } else {
        println!("No");
    }
}
