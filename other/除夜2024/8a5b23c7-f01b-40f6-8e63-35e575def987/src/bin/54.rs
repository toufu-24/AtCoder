use proconio::{input, marker::Chars};

fn main() {
    input! {
        s: [Chars; 8]
    }
    let mut s2 = s.clone();
    for i in 0..8 {
        for j in 0..8 {
            if s[i][j] == '#' {
                for k in 0..8 {
                    s2[i][k] = '#';
                    s2[k][j] = '#';
                }
            }
        }
    }

    let ans = s2
        .iter()
        .map(|x| x.iter().filter(|&&c| c == '.').count())
        .sum::<usize>();
    println!("{}", ans);
}
