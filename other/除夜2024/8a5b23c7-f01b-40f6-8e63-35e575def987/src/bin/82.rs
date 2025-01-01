use proconio::{input, marker::Chars};

fn main() {
    input! {
        a: i64,
        b: i64,
        c: i64,
        d: i64,
        e: i64,
    }

    let mut point = Vec::new();
    for i in 0..1 << 5 {
        let mut sum = 0;
        let mut name = String::new();
        for j in 0..5 {
            if i >> j & 1 == 1 {
                sum += match j {
                    0 => a,
                    1 => b,
                    2 => c,
                    3 => d,
                    4 => e,
                    _ => unreachable!(),
                };
                name += match j {
                    0 => "A",
                    1 => "B",
                    2 => "C",
                    3 => "D",
                    4 => "E",
                    _ => "",
                };
            }
        }

        point.push((sum, name));
    }

    // sumの降順，nameの昇順
    point.sort_by(|a, b| b.0.cmp(&a.0).then(a.1.cmp(&b.1)));

    for (_, name) in point {
        println!("{}", name);
    }
}
