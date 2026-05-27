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
    int m, d;
    cin >> m >> d;
    set<pair<int, int>> st;
    st.insert({1, 7});
    st.insert({3, 3});
    st.insert({5, 5});
    st.insert({7, 7});
    st.insert({9, 9});
    if(st.contains({m,d})){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
}
