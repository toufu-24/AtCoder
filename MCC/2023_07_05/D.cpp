#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (true)
    {
        int ans = 0;
        string S;
        cin >> S;
        if (S == "#")
        {
            break;
        }
        int left_cnt = 0;
        for (int i = 0; i < S.size() && S[i] == ')'; i++)
        {
            left_cnt++;
        }
        int right_cnt = 0;
        for (int i = 0; i < S.size() && S[S.size() - i - 1] == '('; i++)
        {
            right_cnt++;
        }
        ans += (left_cnt + 1) / 2 + (right_cnt + 1) / 2;
        for (int i = 0; i < (left_cnt + 1) / 2; i++)
        {
            S = "(" + S;
        }
        for (int i = 0; i < (right_cnt); i++)
        {
            S += ")";
        }
        cerr << S << endl;
        cerr << ans << endl;
        stack<int> st;
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == '(')
            {
                st.push(i);
            }
            else
            {
            }
        }
    }
}