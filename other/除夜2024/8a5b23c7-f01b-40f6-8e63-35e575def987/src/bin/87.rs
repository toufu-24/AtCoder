use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: i64,
        as_arr: [(i64, Chars); n]
    }

    let mut left_hand = -1;
    let mut right_hand = -1;
    for (a, s) in as_arr.clone() {
        if s == ['L'] {
            if left_hand == -1 {
                left_hand = a;
            }
        } else {
            if right_hand == -1 {
                right_hand = a;
            }
        }
    }

    let mut ans = 0;
    for (a, s) in as_arr {
        if s == ['L'] {
            ans += (left_hand - a).abs();
            left_hand = a;
        } else {
            ans += (right_hand - a).abs();
            right_hand = a;
        }
        // print!("{} ", ans);
    }
    println!("{}", ans);
}
