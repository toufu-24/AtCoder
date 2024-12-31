use proconio::input;

fn main() {
    input! {
        sab: char,
        sac: char,
        sbc: char
    }

    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    if sab == '<' {
        a += 1;
    } else {
        b += 1;
    }
    if sac == '<' {
        a += 1;
    } else {
        c += 1;
    }
    if sbc == '<' {
        b += 1;
    } else {
        c += 1;
    }
    if a == 1 {
        println!("A");
    } else if b == 1 {
        println!("B");
    } else {
        println!("C");
    }
}
