use proconio::input;

fn main() {
    input! {
        n: usize,
        a: [i32; n]
    }
    let max = a.iter().max().unwrap();
    let second_max = a.iter().filter(|&x| x != max).max().unwrap();
    let ans = a.iter().position(|&x| x == *second_max).unwrap();
    println!("{}", ans + 1);
}
