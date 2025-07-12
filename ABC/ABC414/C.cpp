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

#define int long

// https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/base-conversions
/// @brief 数値を指定した基数の文字列表現に変換します。
/// @param n 変換する数値
/// @param base 基数（2～36）
/// @return 変換後の文字列。0 は "0" を返します。
/// @throw std::invalid_argument 基数が範囲外の場合
/// @note 変換後の最大桁数は 64 桁（base が 2 の場合）
/// @note 出典:『競プロのための標準 C++』
[[nodiscard]]
constexpr std::string ToBaseN(unsigned long long n, const unsigned int base) {
    if ((base < 2) || (36 < base)) {
        throw std::invalid_argument{"base must be in the range [2, 36]."};
    }

    constexpr char Digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string s;

    do {
        s.push_back(Digits[n % base]);
        n /= base;
    } while (n);

    std::ranges::reverse(s);
    return s;
}

int32_t main() {
    int a, n;
    cin >> a >> n;
    int max_len = to_string(n).length() / 2 + 1;

    int ans = 0;
    // 123 321 
    // 12321
    auto dfs = [&](auto &&dfs, int x) -> void {
        if (to_string(x).length() > max_len)
            return;

        string s = to_string(x);
        string back = s;
        REVERSE(back);
        s += back;

        int num = stoll(s);
        if (num > 0 && num <= n) {
            string s_a = ToBaseN(num, a);
            string s_a_r = s_a;
            REVERSE(s_a_r);
            if (s_a == s_a_r) {
                ans += num;
            }
        }

        assert(s.size() % 2 == 0);
        s.erase(s.size() / 2, 1);
        string s_r = s;
        REVERSE(s_r);

        num = stoll(s);
        if (num > 0 && num <= n) {
            string s_a = ToBaseN(num, a);
            string s_a_r = s_a;
            REVERSE(s_a_r);
            if (s == s_r && s_a == s_a_r) {
                ans += num;
            }
        }

        for (int i = 0; i <= 9; i++) {
            dfs(dfs, x * 10 + i);
        }
    };
    for (int i = 1; i <= 9; i++) {
        dfs(dfs, i);
    }
    cout << ans << endl;
}
