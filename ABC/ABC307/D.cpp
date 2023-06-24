#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    stack<int> st;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '(')
        {
            st.push(i);
        }
        else if (S[i] == ')')
        {
            if (!st.empty())
            {
                S[st.top()] = '0';
                S[i] = '1';
                st.pop();
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '0')
        {
            cnt++;
        }
        else if (S[i] == '1')
        {
            cnt--;
        }
        else if (cnt == 0)
        {
            cout << S[i];
        }
    }
}