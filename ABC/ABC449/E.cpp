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

int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> cnt(m, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        cnt[a[i]]++;
    }

    int max_cnt = 0;
    for (int i = 0; i < m; i++) {
        max_cnt = max(max_cnt, cnt[i]);
    }

    vector<vector<int>> by_cnt(max_cnt + 1);
    for (int v = 0; v < m; v++) {
        by_cnt[cnt[v]].push_back(v);
    }

    // seq_len[0] は元の配列長、seq_len[level + 1] はその level で追加される長さ
    vector<int> seq_len;
    seq_len.reserve(max_cnt + 2);
    seq_len.push_back(n);
    int active = 0;
    for (int level = 0; level <= max_cnt; level++) {
        active += (int)by_cnt[level].size();
        seq_len.push_back(active);
    }

    vector<int> sum_seq_len(seq_len.size() + 1);
    for (int i = 0; i < seq_len.size(); i++) {
        sum_seq_len[i + 1] = sum_seq_len[i] + seq_len[i];
    }
    int max_size = sum_seq_len.back();

    // 基本的には 1, 2, ..., M, 1, 2, ..., M, 1, 2, ...
    int q;
    cin >> q;
    vector<int> x2(q);
    vector<int> ans(q);
    vector<tuple<int, int, int>> query;
    for (int i = 0; i < q; i++) {
        cin >> x2[i];
        x2[i]--;
        int x = x2[i];
        if (x < n) {
            ans[i] = a[x] + 1;
            continue;
        }
        if (x >= max_size) {
            x -= max_size;
            x %= m;
            ans[i] = x + 1;
            continue;
        }

        int idx = upper_bound(all(sum_seq_len), x) - sum_seq_len.begin();
        idx--;
        int len = seq_len[idx];
        x -= sum_seq_len[idx];
        assert(x < len);
        assert(0 <= x);

        query.push_back({idx - 1, x + 1, i});
    }

    SORT(query);
    fenwick_tree<int> fw(m);
    int level_done = -1;
    for (auto [level, kth, qi] : query) {
        while (level_done < level) {
            level_done++;
            for (auto v : by_cnt[level_done]) {
                fw.add(v, 1);
            }
        }

        int ng = -1;
        int ok = m - 1;
        while (ok - ng > 1) {
            int mid = (ok + ng) / 2;
            if (fw.sum(0, mid + 1) >= kth) {
                ok = mid;
            } else {
                ng = mid;
            }
        }
        ans[qi] = ok + 1;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}
