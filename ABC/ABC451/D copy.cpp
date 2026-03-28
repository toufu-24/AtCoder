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
    int n;
    cin >> n;
    vector<int> kouho;
    int now = 1;
    while (now < 1e9) {
        kouho.push_back(now);
        now *= 2;
    }

    int d = kouho.size();
    cerr << d << endl;

    auto d_shin = ToBaseN(n, d);

    for (auto c : d_shin) {
        int idx = 0;
        if ('0' <= c && c <= '9') {
            idx = c - '0';
        } else {
            idx = c - 'A';
        }
        cout << kouho[idx];
    }
}
