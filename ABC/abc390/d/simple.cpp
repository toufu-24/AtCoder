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

set<int> ans;

void dfs(vector<int> now_arr, int now_xor) {
    int n = now_arr.size();
    if (n == 1) {
        ans.insert(now_xor);
        return;
    }
    for (int in = 0; in < n; in++) {
        for (int recieve = in + 1; recieve < n; recieve++) {
            if (in == recieve) {
                continue;
            }
            vector<int> next_arr = now_arr;
            int next_xor = now_xor ^ now_arr[in] ^ now_arr[recieve];
            next_arr[recieve] += now_arr[in];
            next_xor ^= next_arr[recieve];
            next_arr.erase(next_arr.begin() + in);
            dfs(next_arr, next_xor);
            ans.insert(next_xor);
        }
    }
}

int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int all_xor = 0;
    for (int i = 0; i < n; i++) {
        all_xor ^= a[i];
    }
    ans.insert(all_xor);
    dfs(a, all_xor);
    cout << ans.size() << endl;
}
