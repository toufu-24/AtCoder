use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: Chars,
        t: Chars
    }
    for w in 1..s.len() {
        for c in 1..=w {
            let mut constructed = Vec::new();
            for start in (0..s.len()).step_by(w) {
                let end = (start + w).min(s.len());
                if end - start >= c {
                    constructed.push(s[start + c - 1]);
                }
            }
            if constructed == t {
                println!("Yes");
                return;
            }
        }
    }
    println!("No");
}
