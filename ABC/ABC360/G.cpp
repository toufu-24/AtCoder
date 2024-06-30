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

/// @brief 最長増加部分列（LIS）のインデックスを返します
/// @tparam Strict 狭義単調増加の場合 true, 広義単調増加の場合 false
/// @tparam Type 数列の要素の型
/// @param v 数列
/// @return 最長増加部分列（LIS）のインデックス
/// @note 1.4 最長増加部分列の復元
/// @see
/// https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/lis
template <bool Strict, class Type>
std::vector<int> LIS(const std::vector<Type> &v) {
    std::vector<Type> dp;

    auto it = dp.begin();

    std::vector<int> positions;

    for (const auto &elem : v) {
        if constexpr (Strict) {
            it = std::lower_bound(dp.begin(), dp.end(), elem);
        } else {
            it = std::upper_bound(dp.begin(), dp.end(), elem);
        }

        positions.push_back(static_cast<int>(it - dp.begin()));

        if (it == dp.end()) {
            dp.push_back(elem);
        } else {
            *it = elem;
        }
    }

    std::vector<int> subseq(dp.size());

    int si = static_cast<int>(subseq.size()) - 1;

    int pi = static_cast<int>(positions.size()) - 1;

    while ((0 <= si) && (0 <= pi)) {
        if (positions[pi] == si) {
            subseq[si] = pi;

            --si;
        }

        --pi;
    }

    return subseq;
}

int32_t main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    // 10 20 0 1 30 2
    // 0 1 10 20 30 2
    // インデックス
    auto dp = LIS<true>(A);
    set<int> used = set<int>(dp.begin(), dp.end());
    int ans = dp.size();
    if (dp[0] != 0) {
        ans++;
        cout << ans << endl;
        return 0;
    } else if (dp[dp.size() - 1] != N - 1) {
        ans++;
        cout << ans << endl;
        return 0;
    }

    for (int i = 0; i < dp.size() - 1; i++) {
        if (A[dp[i]] + 1 != A[dp[i + 1]]) {
            // すきまがあるなら
            if (dp[i] + 1 != dp[i + 1]) {
                ans++;
            } else if (dp[i] != 0 && A[dp[i]] == A[dp[i] - 1] &&
                       !used.contains(dp[i] - 1)) {
                ans++;
            } else if (dp[i + 1] != dp.size() - 1 &&
                       A[dp[i + 1]] == A[dp[i + 1] + 1] &&
                       !used.contains(dp[i + 1] + 1)) {
                ans++;
            } else {
                continue;
            }
            break;
        }
    }
    cout << ans << endl;
}
