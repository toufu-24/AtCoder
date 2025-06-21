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
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, string>> query;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p;
            cin >> p;
            p--;
            query.push_back({op, p, ""});
        } else if (op == 2) {
            int p;
            string s;
            cin >> p >> s;
            p--;
            query.push_back({op, p, s});
        } else if (op == 3) {
            int p;
            cin >> p;
            p--;
            query.push_back({op, p, ""});
        }
    }

    string server = "";
    int server_idx = -1;
    for (int i = query.size() - 1; i >= 0; i--) {
        auto [op, p, s] = query[i];
        if (op == 1) {
            if (server_idx == p) {
                server_idx = -1;
            }
        } else if (op == 2) {
            if (server_idx == p) {
                REVERSE(s);
                server += s;
            }
        } else if (op == 3) {
            if (server_idx == -1) {
                server_idx = p;
            }
        }
    }

    REVERSE(server);
    cout << server << endl;
}
