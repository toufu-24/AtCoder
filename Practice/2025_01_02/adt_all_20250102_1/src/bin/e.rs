use proconio::input;

fn main() {
    input! {
        d: i64
    }

    let mut ans = 1e18 as i64;
    let mut i = 0;
    while i * i <= d {
        let mut left = 0;
        let mut right = 1e9 as i64;
        while right - left > 2 {
            let mid1 = (left * 2 + right) / 3;
            let mid2 = (left + right * 2) / 3;
            let f1 = (i * i + mid1 * mid1 - d).abs();
            let f2 = (i * i + mid2 * mid2 - d).abs();
            if f1 < f2 {
                right = mid2;
            } else {
                left = mid1;
            }
        }
        for j in -3..=3 {
            if left + j >= 0 {
                ans = ans.min((i * i + (left + j) * (left + j) - d).abs());
            }
        }
        i += 1;
    }
    println!("{}", ans);
}
