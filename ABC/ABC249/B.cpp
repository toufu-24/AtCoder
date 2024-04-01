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
    bool small = false, large = false;
    set<char> st;
    for (int i = 0; i < S.size(); i++)
    {
        if (isupper(S[i]))
        {
            large = true;
        }
        else
        {
            small = true;
        }
        st.insert(S[i]);
    }
    if (st.size() == S.size() && small && large)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
