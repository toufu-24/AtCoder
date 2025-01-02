use proconio::input;

fn main() {
    input! {
        n: usize,
    }

    let mut graph = vec![vec![]; n];
    for i in 1..=n {
        input! {
            d: [usize; n - i]
        }
        let d = d.iter().map(|x| x - 1).collect::<Vec<usize>>();
        for j in 0..i - 1 {
            graph[i].push(d[j]);
            graph[d[j]].push(i);
        }
    }

    let mut ans = 0;
    for mask in 0..1 << n {
        let mut flag = true;
        let mut used = vec![false; n];
        for i in 0..n {
            if mask >> i & 1 == 1 {
                
            }
        }
    }
}
