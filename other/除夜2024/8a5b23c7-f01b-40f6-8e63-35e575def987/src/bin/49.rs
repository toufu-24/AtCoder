use proconio::input;

fn main() {
    input! {
        s: String,
    }
    if s.ends_with("san") {
        println!("Yes");
    } else {
        println!("No");
    }
}
