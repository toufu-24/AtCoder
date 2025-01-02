use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        m: usize,
        mut s: [Chars; n],
    }

    for i in 0..=n - 9 {
        for j in 0..=m - 9 {
            // i,jの位置から9マス×9マスを取得
            let nine_speareted = s
                .iter()
                .skip(i)
                .take(9)
                .map(|x| x.iter().skip(j).take(9).collect::<Vec<_>>())
                .collect::<Vec<_>>();

            let mut count = 0;
            for k in 0..3 {
                for l in 0..3 {
                    if nine_speareted[k][l] == &'#' {
                        count += 1;
                    }
                    if nine_speareted[9 - k - 1][9 - l - 1] == &'#' {
                        count += 1;
                    }
                }
            }
            if count != 18 {
                continue;
            }

            let mut flag = true;
            for ii in 0..4 {
                if nine_speareted[3][ii] != &'.' {
                    flag = false;
                    break;
                }
                if nine_speareted[ii][3] != &'.' {
                    flag = false;
                    break;
                }
                if nine_speareted[5][9 - 1 - ii] != &'.' {
                    flag = false;
                    break;
                }
                if nine_speareted[9 - 1 - ii][5] != &'.' {
                    flag = false;
                    break;
                }
            }
            if flag {
                println!("{} {}", i + 1, j + 1);
            }
        }
    }
}
