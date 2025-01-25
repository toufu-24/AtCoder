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

static uint32_t randXor() {
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 0以上1未満の小数をとる乱数
static double rand01() {
    return (randXor() + 0.5) * (1.0 / UINT_MAX);
}

int calc_score(vector<int> a) {
    return *min_element(all(a));
}
using namespace chrono;
int32_t main() {
    clock_t start = clock();
    int n, x;
    cin >> n >> x;
    vector<int> v(n), a(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> a[i] >> c[i];
    }
    vector<tuple<int, int, int, int>> ones, twos, threes;
    for (int i = 0; i < n; i++) {
        if (v[i] == 1) {
            ones.push_back({v[i], a[i], c[i], i});
        } else if (v[i] == 2) {
            twos.push_back({v[i], a[i], c[i], i});
        } else {
            threes.push_back({v[i], a[i], c[i], i});
        }
    }
    sort(all(ones), [](tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
        return (ld)(get<1>(a)) / get<2>(a) < (ld)(get<1>(b)) / get<2>(b);
    });
    sort(all(twos), [](tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
        return (ld)(get<1>(a)) / get<2>(a) < (ld)(get<1>(b)) / get<2>(b);
    });
    sort(all(threes), [](tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
        return (ld)(get<1>(a)) / get<2>(a) < (ld)(get<1>(b)) / get<2>(b);
    });

    vector<vector<tuple<int, int, int, int>>> arr = {ones, twos, threes};
    vector<int> idxes(3, 0);
    vector<int> sums(3, 0);
    int now_calories = 0;
    vector<set<int>> used(3);
    while (now_calories <= x) {
        int min_idx = -1;
        int min_val = 1e18;
        for (int i = 0; i < 3; i++) {
            if (idxes[i] < arr[i].size() && sums[i] < min_val) {
                min_val = sums[i];
                min_idx = i;
            }
        }

        if (min_idx == -1)
            break;

        if (now_calories + get<2>(arr[min_idx][idxes[min_idx]]) > x)
            break;

        sums[min_idx] += get<1>(arr[min_idx][idxes[min_idx]]);
        now_calories += get<2>(arr[min_idx][idxes[min_idx]]);
        idxes[min_idx]++;
        used[min_idx].insert(get<3>(arr[min_idx][idxes[min_idx]]));
    }

    // sumsが一番小さいものの中からひとつ選んで，違うやつとswapする
    // やきなまし
    int now_score = calc_score(sums);
    int best_score = now_score;
    ld start_temp = 1500;
    ld end_temp = 100;
    do {
        int bit = randXor() % 2;
        if (bit == 0) {
            int min_idx = -1;
            int min_val = 1e18;
            for (int i = 0; i < 3; i++) {
                if (idxes[i] < arr[i].size() && sums[i] < min_val) {
                    min_val = sums[i];
                    min_idx = i;
                }
            }
            if (min_idx == -1)
                break;
            bool ok = false;
            for (int i = 0; i < 3; i++) {
                if (used[min_idx].size() != arr[min_idx].size()) {
                    ok = true;
                    break;
                }
                min_idx = (min_idx + 1) % 3;
            }
            if (!ok)
                continue;

            int insert = randXor() % n;
            while ((used[min_idx].contains(insert) || now_calories + get<1>(arr[min_idx][insert]) > x) && (clock() - start < 1.9 * CLOCKS_PER_SEC)) {
                insert = randXor() % n;
            }
            if ((clock() - start > 1.9 * CLOCKS_PER_SEC)) {
                break;
            }
            sums[min_idx] += get<1>(arr[min_idx][insert]);
            used[min_idx].insert(insert);
            now_calories += get<2>(arr[min_idx][insert]);
            int next_score = calc_score(sums);
            int diff = next_score - now_score;
            diff = -diff;

            if (diff < 0) {
                best_score = max(best_score, next_score);
            } else {
                ld time = (ld)(clock() - start) / CLOCKS_PER_SEC;
                ld temp = start_temp + (end_temp - start_temp) * time / 2;
                ld prob = exp(-diff / temp);
                if (rand01() < prob) {
                    best_score = max(best_score, next_score);
                } else {
                    sums[min_idx] -= get<1>(arr[min_idx][insert]);
                    used[min_idx].erase(insert);
                    now_calories -= get<2>(arr[min_idx][insert]);
                }
            }
        } else {
            int max_idx = -1;
            int max_val = -1;
            for (int i = 0; i < 3; i++) {
                if (idxes[i] < arr[i].size() && sums[i] > max_val) {
                    max_val = sums[i];
                    max_idx = i;
                }
            }
            if (max_idx == -1)
                break;
            bool ok = false;
            for (int i = 0; i < 3; i++) {
                if (used[max_idx].size() != 0) {
                    ok = true;
                    break;
                }
                max_idx = (max_idx + 1) % 3;
            }
            if (!ok)
                continue;

            int erase = randXor() % arr[max_idx].size();
            while (!used[max_idx].contains(erase) && (clock() - start < 1.9 * CLOCKS_PER_SEC)) {
                erase = randXor() % arr[max_idx].size();
            }
            if ((clock() - start > 1.9 * CLOCKS_PER_SEC)) {
                break;
            }
            sums[max_idx] -= get<1>(arr[max_idx][erase]);
            used[max_idx].erase(erase);
            now_calories -= get<2>(arr[max_idx][erase]);
            int next_score = calc_score(sums);
            int diff = next_score - now_score;
            diff = -diff;
            if (diff < 0) {
                best_score = max(best_score, next_score);
            } else {
                ld time = (ld)(clock() - start) / CLOCKS_PER_SEC;
                ld temp = start_temp + (end_temp - start_temp) * time / 2;
                ld prob = exp(-diff / temp);
                if (rand01() < prob) {
                    best_score = max(best_score, next_score);
                } else {
                    sums[max_idx] += get<1>(arr[max_idx][erase]);
                    used[max_idx].insert(erase);
                    now_calories += get<2>(arr[max_idx][erase]);
                }
            }
        }
    } while (clock() - start < 1.9 * CLOCKS_PER_SEC);

    cout << calc_score(sums) << endl;
    for (auto x : sums) {
        cerr << x << " ";
    }
    cerr << endl;
}
