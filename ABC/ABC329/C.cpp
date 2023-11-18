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

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    set<string> st;
    string tmp = "";
    tmp += S[0];
    st.insert(tmp);
    for (int i = 1; i < N; i++)
    {
        if (S[i] == S[i - 1])
        {
            tmp += S[i];
            st.insert(tmp);
        }
        else
        {
            st.insert(tmp);
            tmp = "";
            tmp += S[i];
            st.insert(tmp);
        }
    }
    st.insert(tmp);
    cout << st.size() << endl;
}