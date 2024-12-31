use proconio::input;

fn main() {
    input! {
        n: usize,
        k: i32,
        r: [i32; n],
    }

    let mut ans = Vec::new();

    fn dfs(arr: &mut Vec<i32>, ans: &mut Vec<Vec<i32>>, n: usize, r: &[i32], k: i32, sum: i32) {
        if arr.len() == n {
            if sum % k == 0 {
                ans.push(arr.clone());
            }
            return;
        }

        let idx = arr.len();
        for i in 1..=r[idx] {
            arr.push(i);
            dfs(arr, ans, n, r, k, sum + i);
            arr.pop();
        }
    }

    dfs(&mut Vec::new(), &mut ans, n, &r, k, 0);

    for a in &ans {
        for i in a {
            print!("{} ", i);
        }
        println!();
    }
}
