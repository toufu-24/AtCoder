#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
// #define ll long
#define ld long double

// #define int ll
#define int long long

// https://0214sh7.github.io/library/posts/arg-sort
// Copyright (c) 2024 0214sh7
// https://github.com/0214sh7/library/
std::vector<std::pair<long long, long long>> arg_sort(std::vector<std::pair<long long, long long>> A, std::pair<long long, long long> d = {1, 0}) {
    // Copyright (c) 2023 0214sh7
    // https://github.com/0214sh7/library/
    long long N = A.size();
    assert(d.first != 0 || d.second != 0);
    long long g = std::gcd(d.first, d.second);
    d.first /= g;
    d.second /= g;
    A.push_back(d);
    std::sort(A.begin(), A.end(), [&](std::pair<long long, long long> x, std::pair<long long, long long> y) {
        assert(x.first != 0 || x.second != 0);
        assert(y.first != 0 || y.second != 0);

        long long a, b;
        if (x.first > 0 && x.second == 0) {
            a = 0;
        } else if (x.first > 0 && x.second > 0) {
            a = 1;
        } else if (x.first == 0 && x.second > 0) {
            a = 2;
        } else if (x.first < 0 && x.second > 0) {
            a = 3;
        } else if (x.first < 0 && x.second == 0) {
            a = 4;
        } else if (x.first < 0 && x.second < 0) {
            a = 5;
        } else if (x.first == 0 && x.second < 0) {
            a = 6;
        } else {
            a = 7;
        }

        if (y.first > 0 && y.second == 0) {
            b = 0;
        } else if (y.first > 0 && y.second > 0) {
            b = 1;
        } else if (y.first == 0 && y.second > 0) {
            b = 2;
        } else if (y.first < 0 && y.second > 0) {
            b = 3;
        } else if (y.first < 0 && y.second == 0) {
            b = 4;
        } else if (y.first < 0 && y.second < 0) {
            b = 5;
        } else if (y.first == 0 && y.second < 0) {
            b = 6;
        } else {
            b = 7;
        }

        if (a != b) {
            return (a < b);
        }

        if (a % 2 == 0) {
            return (std::abs(x.first + x.second) < std::abs(y.first + y.second));
        }

        if (y.first * x.second != x.first * y.second) {
            return (y.first * x.second < x.first * y.second);
        }

        return abs(x.first) < abs(y.first);
    });

    std::vector<std::pair<long long, long long>> B(N);
    for (int i = 0; i < N + 1; i++) {
        if (A[i] == d) {
            for (int j = i + 1; j < N + 1; j++) {
                B[j - i - 1] = A[j];
            }
            for (int j = 0; j < i; j++) {
                B[N - i + j] = A[j];
            }
            break;
        }
    }

    return B;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> xy(n);
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
            xy[i] = {x[i], y[i]};
        }
        xy = arg_sort(xy);
        for (int i = 0; i < n; i++) {
            auto [xx, yy] = xy[i];
            x[i] = xx;
            y[i] = yy;
        }

        for (int i = 0; i < n; i++) {
            x.push_back(x[i]);
            y.push_back(y[i]);
        }

        // 一個の星を基準に180度取れる
        // 尺取り？
        int ans = 0;
        int left = 0, right = 1;
        while (left < n) {
            // leftから180度まわしたやつとrightを比較する
            while (right < 2 * n && left + n > right) {
                int lx18 = -x[left];
                int ly18 = -y[left];
                int rx = x[right];
                int ry = y[right];
                pair<int, int> l18 = {lx18, ly18};
                pair<int, int> r = {rx, ry};
                vector<pair<int, int>> tmp;
                tmp.push_back(l18);
                tmp.push_back(r);

                pair<int, int> mea = {lx18 + rx, ly18 + ry};

                tmp = arg_sort(tmp, mea);
                // 0が後ろ
                if (tmp[0] == r) {
                    break;
                } else {
                    right++;
                }
            }
            ans = max({ans, right - left, n - (right - left)});

            left++;
            if (left >= right) {
                right = left + 1;
            }
        }

        // for (int i = 0; i < 2 * n; i++) {
        //     x[i] *= -1;
        //     y[i] *= -1;
        // }

        // left = 0, right = 0;
        // while (left < n) {
        //     // leftから180度まわしたやつとrightを比較する
        //     while (right < 2 * n) {
        //         int lx18 = -x[left];
        //         int ly18 = -x[left];
        //         int rx = x[right];
        //         int ry = y[right];
        //         pair<int, int> l18 = {lx18, ly18};
        //         pair<int, int> r = {rx, ry};
        //         vector<pair<int, int>> tmp;
        //         tmp.push_back(l18);
        //         tmp.push_back(r);

        //         pair<int, int> mea = {lx18 + rx, ly18 + ry};

        //         tmp = arg_sort(tmp, mea);
        //         // 0が後ろ
        //         if (tmp[0] == r) {
        //             break;
        //         } else {
        //             right++;
        //         }
        //     }
        //     ans = max(ans, right - left);

        //     if (left == right) {
        //         right++;
        //     }
        //     left++;
        // }

        cout << ans << endl;
    }
}
