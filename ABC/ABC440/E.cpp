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
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    RSORT(a);
    vector<int> ans;
    int base = *a.begin() * k;
    priority_queue<tuple<int, vector<int>>> pq;
    vector<int> tmp(n, 0);
    tmp[0] = k;
    pq.push({base, tmp});
    set<vector<int>> st;
    st.insert(tmp);
    for (int kk = 0; kk < x; kk++) {
        auto [score, cookies] = pq.top();
        pq.pop();
        ans.push_back(score);
        for (int i = 0; i < n - 1; i++) {
            if (cookies[i] == 0) {
                continue;
            }
            int j = i + 1;
            // cookie iを1つjにする
            cookies[i]--;
            cookies[j]++;
            if (!st.contains(cookies)) {
                st.insert(cookies);
                pq.push({score + a[j] - a[i], cookies});
            }
            cookies[i]++;
            cookies[j]--;
        }
    }
    assert(ans.size() == x);
    for (auto xx : ans) {
        cout << xx << "\n";
    }
}
