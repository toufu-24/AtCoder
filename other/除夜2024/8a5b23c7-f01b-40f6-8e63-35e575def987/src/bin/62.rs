use proconio::input;

fn main() {
    input! {
        n: i64,
        _x: i64,
        _y: i64,
        z: i64,
    }
    let mut x = _x.min(_y);
    let mut y = _x.max(_y);
    loop {
        if y < x {
            break;
        }
        if x == z {
            println!("Yes");
            return;
        }
        x += 1;
    }
    println!("No");
}
