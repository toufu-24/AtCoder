use ac_library::{LazySegtree, MapMonoid, Monoid};
use itertools::Itertools;
use proconio::input;

// セグメント木で使用するモノイドの定義
struct Min;
impl Monoid for Min {
    type S = usize;

    fn identity() -> Self::S {
        usize::MAX // 初期値は十分大きな値（最小値を取るため）
    }

    fn binary_operation(&a: &Self::S, &b: &Self::S) -> Self::S {
        a.min(b) // 区間の最小値を取る
    }
}

// 区間加算の定義
struct Add;
impl MapMonoid for Add {
    type M = Min;
    type F = usize; // 加算する値

    fn identity_map() -> Self::F {
        0 // 加算操作の単位元は 0
    }

    fn mapping(&f: &Self::F, &x: &<Self::M as Monoid>::S) -> <Self::M as Monoid>::S {
        x + f // 現在の値に加算
    }

    fn composition(&f: &Self::F, &g: &Self::F) -> Self::F {
        f + g // 加算操作の合成
    }
}

fn main() {
    input! {
        n: usize,
        a: [usize; n],
    }
    let mut segtree: LazySegtree<Add> = a.into_iter().collect_vec().into();
    for i in 0..n {
        // for j in 0..n {
        //     print!("{} ", segtree.get(j));
        // }
        // println!();
        let x = segtree.get(i);
        if i + x < n {
            segtree.apply_range(i + 1..=i + x, 1);
            segtree.set(i, 0);
        } else {
            segtree.apply_range(i + 1..n, 1);
            segtree.set(i, x - (n - i) + 1);
        }
    }

    for i in 0..n {
        print!("{} ", segtree.get(i));
    }
    println!();
}
