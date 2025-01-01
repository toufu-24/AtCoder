use proconio::input;

fn main() {
    input! {
        mut s : String
    }
    s.remove(0);
    s.remove(0);
    s.remove(0);
    let num = s.parse::<i32>().unwrap();
    if 1 <= num && num <= 349 && num != 316 {
        println!("Yes");
    } else {
        println!("No");
    }
}
