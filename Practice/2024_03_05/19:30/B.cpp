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
    stack<string> st;
    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        st.push(s);
    }
    while (!st.empty())
    {
        cout << st.top() << endl;
        st.pop();
    }
}