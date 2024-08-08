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

// https://qiita.com/drken/items/a14e9af0ca2d857dad23
vector<int> enum_divisors(int N) {
    vector<int> res;
    for (int i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            res.push_back(i);
            // 重複しないならば i の相方である N/i も push
            if (N / i != i) res.push_back(N / i);
        }
    }
    // 小さい順に並び替える
    sort(res.begin(), res.end());
    return res;
}

int32_t main() {
    int N;
    cin >> N;
    N *= 2;
    auto divs = enum_divisors(N);
    int ans = 0;
    for (int i = 0; i < divs.size(); i++) {
        int lower = divs[i];
        int upper = N / divs[i];
        if (lower > upper) break;

        // lower := b-a+1, upper := a+b となるa, bの個数
        int b = (lower + upper - 1) / 2;
        int a = upper - b;
        if ((lower + upper - 1) % 2 == 0) {
            ans += 2;
        }
    }

    cout << ans << endl;
}
