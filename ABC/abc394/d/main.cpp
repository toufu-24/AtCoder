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
    string s;
    cin >> s;
    bool ans = true;
    stack<char> st;
    vector<char> begin = {'(', '<', '['};
    vector<char> end = {')', '>', ']'};
    for (int i = 0; i < s.size(); i++) {
        if (find(all(begin), s[i]) != begin.end()) {
            st.push(s[i]);
        } else if (find(all(end), s[i]) != end.end()) {
            if (st.empty()) {
                ans = false;
                break;
            }
            char c = st.top();
            st.pop();
            if (find(all(begin), c) - begin.begin() != find(all(end), s[i]) - end.begin()) {
                ans = false;
                break;
            }
        }
    }
    if (st.empty() && ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
