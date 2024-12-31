use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i64; n],
    }

    if n == 1 {
        println!("1");
        return;
    }

    let mut left = 0usize;
    let mut right = 0usize;
    let mut ans = n;
    let mut d = a[1] - a[0];

    while left < n {
        while right < n - 1 && a[right + 1] - a[right] == d {
            right += 1;
        }

        if right > left {
            let length = right - left + 1;
            ans += (length) * (length - 1) / 2;
        }

        left = right;
        if left < n - 1 {
            right = left + 1;
            d = a[right] - a[left];
        } else {
            break;
        }
    }

    println!("{}", ans);
}
