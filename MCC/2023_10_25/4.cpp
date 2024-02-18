#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;

    int left_shortage = 0;
    int right_shortage = 0;
    stack<char> left_st;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == '(')
        {
            left_st.push('(');
        }
        else
        {
            if (left_st.empty())
            {
                left_shortage++;
            }
            else
            {
                left_st.pop();
            }
        }
    }
    for (int i = 0; i < left_shortage; i++)
    {
        S = '(' + S;
    }

    cerr << S;
    stack<char> right_st;
    for (int i = S.size() - 1; i >= 0; i--)
    {
        if (S[i] == ')')
        {
            right_st.push(')');
        }
        else
        {
            if (right_st.empty())
            {
                right_shortage++;
            }
            else
            {
                right_st.pop();
            }
        }
    }

    for (int i = 0; i < right_shortage; i++)
    {
        S = S + ')';
    }
    cout << S << endl;
}