#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

using mint = modint998244353;

// https://algo-method.com/descriptions/84
// N の約数をすべて求める関数
vector<int> calc_divisors(int N) {
    // 答えを表す集合
    vector<int> res;

    // 各整数 i が N の約数かどうかを調べる
    for (int i = 1; i * i <= N; ++i) {
        // i が N の約数でない場合はスキップ
        if (N % i != 0)
            continue;

        // i は約数である
        res.push_back(i);

        // N ÷ i も約数である (重複に注意)
        if (N / i != i)
            res.push_back(N / i);
    }

    // 約数を小さい順に並び替えて出力
    sort(res.begin(), res.end());
    return res;
}

int32_t main() {
    int n;
    cin >> n;
    // a,bだけ考えればいい！ <- 天才
    // a -> 自由
    // b -> aの約数で無ければいい
    // sum_k=1^n (k - d(k))

    mint ans = 0;
    for (int a = 1; a <= n; a++) {
        vector<int> divisors = calc_divisors(a);
        ans += a - divisors.size();
    }

    cout << ans.val() << endl;
}
