#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long long
#define ld long double

#define int ll

// stringにどの深さで到達したかを記録
map<string, int> memo;
int dfs(int depth, string S, const string &T) {
    if (S.substr(0, T.size()) == T) {
        return depth;
    }
    if (memo.count(S) && memo[S] < depth + 1) {
        return 1e18;
    }
    int dot_idx = S.find("..");
    assert(dot_idx != S.size() - 1);
    int res = 1e18;
    memo[S] = depth;
    for (int i = 0; i < S.size() - 1; i++) {
        if (i == dot_idx || i == dot_idx - 1 || i == dot_idx + 1) {
            continue;
        }
        // iからの2文字を..とswap
        string tmp = S.substr(i, 2);
        S[dot_idx] = tmp[0];
        S[dot_idx + 1] = tmp[1];
        S[i] = '.';
        S[i + 1] = '.';
        int res_in = 1e18;
        if (memo.count(S) && memo[S] < depth + 1) {
            res_in = 1e18;
        } else {
            res_in = dfs(depth + 1, S, T);
        }

        res = min(res, res_in);
        S[i] = tmp[0];
        S[i + 1] = tmp[1];
        S[dot_idx] = '.';
        S[dot_idx + 1] = '.';
    }

    return res;
}

int32_t main() {
    int N;
    cin >> N;
    string S, T;
    cin >> S >> T;
    S += "..";

    int W_cnt = count(S.begin(), S.end(), 'W');
    int B_cnt = count(T.begin(), T.end(), 'B');

    if (W_cnt != B_cnt) {
        cout << -1 << endl;
        return 0;
    }

    int ans = dfs(0, S, T);
    cout << (ans == 1e18 ? -1 : ans) << endl;
}