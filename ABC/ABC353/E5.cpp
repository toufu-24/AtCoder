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

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int BASE1 = 31;
const int BASE2 = 37;

pair<vector<int>, vector<int>> compute_hashes(const string &s)
{
    int n = s.size();
    vector<int> hashes1(n + 1, 0), hashes2(n + 1, 0);
    vector<int> powers1(n + 1, 1), powers2(n + 1, 1);
    for (int i = 0; i < n; i++)
    {
        hashes1[i + 1] = (hashes1[i] * BASE1 + s[i]) % MOD1;
        powers1[i + 1] = (powers1[i] * BASE1) % MOD1;
        hashes2[i + 1] = (hashes2[i] * BASE2 + s[i]) % MOD2;
        powers2[i + 1] = (powers2[i] * BASE2) % MOD2;
    }
    return {hashes1, hashes2};
}

pair<int, int> get_hash(const vector<int> &hashes1, const vector<int> &powers1, const vector<int> &hashes2, const vector<int> &powers2, int l, int r)
{
    int hash_value1 = (hashes1[r] - hashes1[l] * powers1[r - l] % MOD1 + MOD1) % MOD1;
    int hash_value2 = (hashes2[r] - hashes2[l] * powers2[r - l] % MOD2 + MOD2) % MOD2;
    return {hash_value1, hash_value2};
}

int32_t main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
    }
    SORT(S);

    map<pair<int, int>, int> prefix;
    for (int i = 0; i < N; i++)
    {
        auto [hashes1, hashes2] = compute_hashes(S[i]);
        for (int j = 1; j <= S[i].size(); j++)
        {
            auto hash_value = get_hash(hashes1, hashes1, hashes2, hashes2, 0, j);
            prefix[hash_value] = max(prefix[hash_value], i);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++)
    {
        vector<int> cnt(S[i].size() + 2, 0);
        auto [hashes1, hashes2] = compute_hashes(S[i]);
        for (int size = 1; size <= S[i].size(); size++)
        {
            auto hash_value = get_hash(hashes1, hashes1, hashes2, hashes2, 0, size);
            int idx = prefix[hash_value];
            cnt[size] = max(0L, idx - i);
        }
        for (int size = 1; size <= S[i].size(); size++)
        {
            ans += (cnt[size] - cnt[size + 1]) * size;
        }
    }
    cout << ans << endl;
}
