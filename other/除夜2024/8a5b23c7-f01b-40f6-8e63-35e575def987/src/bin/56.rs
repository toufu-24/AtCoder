use proconio::input;

fn main() {
    input! {
        y: i32,
    }
    fn is_leap_year(year: i32) -> bool {
        (year % 4 == 0 && year % 100 != 0) || year % 400 == 0
    }
    if is_leap_year(y) {
        println!("366");
    } else {
        println!("365");
    }
}
