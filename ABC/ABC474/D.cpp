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

int ipow(int n, int p) {
    int ret = 1;
    for (int i = 0; i < p; i++) {
        ret *= n;
    }
    return ret;
}

// 1 以上 N 以下の整数が素数かどうかを返す
vector<bool> Eratosthenes(int N) {
    // テーブル
    vector<bool> isprime(N + 1, true);

    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p) {
        // すでに合成数であるものはスキップする
        if (!isprime[p])
            continue;

        // p 以外の p の倍数から素数ラベルを剥奪
        for (int q = p * 2; q <= N; q += p) {
            isprime[q] = false;
        }
    }

    // 1 以上 N 以下の整数が素数かどうか
    return isprime;
}

int32_t main() {
    string s;
    cin >> s;
    auto isprime = Eratosthenes(1e7 + 1);
    map<char, vector<int>> mp;
    for (int i = 0; i < s.size(); i++) {
        mp[s[i]].push_back(i);
    }

    vector<vector<int>> same(mp.size());
    int idx = 0;
    for (auto [key, val] : mp) {
        // same[idx]
        for (auto x : val) {
            same[idx].push_back(x);
        }
        idx++;
    }

    int si = 7;
    // 長さ s.size() の十進数
    int e = ipow(10, s.size());
    for (int i = ipow(10, s.size() - 1); i < e; i++) {
        if (!isprime[i]) {
            continue;
        }
        string ist = to_string(i);
        // istがsを満たしているか
        map<char, char> m;
        bool ok = true;
        for (int i = 0; i < s.size(); i++) {
            if (m.contains(ist[i])) {
                if (m[ist[i]] != s[i]) {
                    ok = false;
                }
            } else {
                m[ist[i]] = s[i];
            }
        }

        map<char, char> m2;
        for (int i = 0; i < s.size(); i++) {
            if (m2.contains(s[i])) {
                if (m2[s[i]] != ist[i]) {
                    ok = false;
                }
            } else {
                m2[s[i]] = ist[i];
            }
        }

        if (ok) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
// 1000000