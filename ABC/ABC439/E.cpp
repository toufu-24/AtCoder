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

/// @brief 最長増加部分列（LIS）の長さを返します（狭義単調増加）
/// @tparam Type 数列の要素の型
/// @param v 数列
/// @return 最長増加部分列（LIS）の長さ
/// @note 1.1 最長増加部分列の長さの取得（狭義単調増加）
/// @see https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/lis
template <class Type>
size_t LIS(const std::vector<Type> &v) {
    std::vector<Type> dp;

    for (const auto &elem : v) {
        auto it = std::lower_bound(dp.begin(), dp.end(), elem);

        if (it == dp.end()) {
            dp.push_back(elem);
        } else {
            *it = elem;
        }
    }

    return dp.size();
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<pair<int, int>> ab;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        ab.push_back({a[i], b[i]});
    }
    sort(all(ab), [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    // (a_i - a_j) * (b_i - b_j) > 0 であれば交差しない
    // a_i < a_{i+1} de固定すると
    // b_i < b_{i+1} であればいい？
    vector<int> sorted_b(n);
    for (int i = 0; i < n; i++) {
        sorted_b[i] = ab[i].second;
    }

    cout << LIS(sorted_b) << endl;
}
