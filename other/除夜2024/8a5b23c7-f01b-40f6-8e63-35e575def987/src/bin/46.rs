use proconio::input;

fn main() {
    input! {
        s: String,
    }
    let key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    let mut hand = s.find('A').unwrap() as i32;
    let mut ans = 0;
    for c in key.chars() {
        let index = s.find(c).unwrap() as i32;
        ans += (hand - index).abs();
        hand = index;
    }
    println!("{}", ans);
}
