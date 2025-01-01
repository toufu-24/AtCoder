use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: Chars
    }
    let mut one = 0;
    let mut two = 0;
    let mut three = 0;
    for i in n {
        if i == '1' {
            one += 1;
        } else if i == '2' {
            two += 1;
        } else if i == '3' {
            three += 1;
        }
    }
    if one == 1 && two == 2 && three == 3 {
        println!("Yes");
    } else {
        println!("No");
    }
}
