use proconio::input;

fn main() {
    input! {
        mut a: [i32; 4]
    }
    let mut ans = 0;
    a.sort();
    let mut i = 0;
    while i < a.len() - 1 {
        if a[i] == a[i + 1] {
            ans += 1;
            i += 2;
        } else {
            i += 1;
        }
    }
    println!("{}", ans);
}
