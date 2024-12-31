use proconio::input;

fn main() {
    input! {
        n: usize,
        mut sc: [(String, i32); n]
    }
    sc.sort();
    let t: i32 = sc.iter().map(|(_, value)| value).sum();
    println!("{}", sc[t as usize % n].0);
}
