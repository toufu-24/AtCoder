use proconio::input;

fn main() {
    input! {
        n: usize,
    mut a: [usize; n],
    }

    let mut left = 0;
    let mut right = n/2+1;
    while right - left > 1 {
        let mid = (left + right) / 2;
        let small = a.iter().take(mid).collect::<Vec<_>>();
        let large = a.iter().skip(n - mid).collect::<Vec<_>>();
        assert!(small.len() == mid);
        assert!(large.len() == mid);
        let mut ok = true;
        for i in 0..mid {
            if small[i] * 2 > *large[i] {
                ok = false;
                break;
            }
        }
        if ok {
            left = mid;
        } else {
            right = mid;
        }
    }
    println!("{}", left);
}
