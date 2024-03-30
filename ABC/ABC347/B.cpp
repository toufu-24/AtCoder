#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    string S;
    cin >> S;
    set<string> st;
    for (int i = 0; i < S.size(); i++)
    {
        for (int j = i; j < S.size(); j++)
        {
            string s = S.substr(i, j - i + 1);
            st.insert(s);
        }
    }
    cout << st.size() << endl;
}
