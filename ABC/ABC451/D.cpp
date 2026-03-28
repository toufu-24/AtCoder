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
    int n;
    cin >> n;
    vector<int> kouho;
    int nownow = 1;
    while (nownow < 1e9) {
        kouho.push_back(nownow);
        nownow *= 2;
    }

    int d = kouho.size();
    cerr << d << endl;

    set<int> ans;
    set<int> st;
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(0);
    while (!pq.empty()) {
        int now = pq.top();
        pq.pop();
        ans.insert(now);
        // cerr << ans.size() << endl;
        if (ans.size() == n + 1) {
            cout << now << endl;
            return 0;
        }
        string now_st = to_string(now);
        if (now == 0) {
            now_st = "";
        }
        for (auto x : kouho) {
            string tmp = now_st + to_string(x);
            int tmp_int = stoll(tmp);
            if (tmp_int > 1e9) {
                break;;
            }
            if (!st.contains(tmp_int)) {
                pq.push(tmp_int);
                st.insert(tmp_int);
            }
            // if (!st.contains(stoll(to_string(x) + now_st))){
            //     pq.push(stoll(to_string(x) + now_st));
            //     st.insert(stoll(to_string(x) + now_st));
            // }
        }
    }
}
