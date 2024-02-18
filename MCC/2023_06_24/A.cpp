#include <bits/stdc++.h>
using namespace std;

int main()
{
    while (1)
    {
        string S;
        cin >> S;
        if (S == "#")
        {
            break;
        }
        vector<char> komoji;
        vector<char> oomoji;
        vector<char> number;
        for (int i = 0; i < S.size(); i++)
        {
            if ('a' <= S[i] && S[i] <= 'z')
            {
                komoji.push_back(S[i]);
            }
            else if ('A' <= S[i] && S[i] <= 'Z')
            {
                oomoji.push_back(S[i]);
            }
            else if ('0' <= S[i] && S[i] <= '9')
            {
                number.push_back(S[i]);
            }
        }
        sort(komoji.begin(), komoji.end());
        sort(oomoji.begin(), oomoji.end());
        sort(number.begin(), number.end());

        for (int i = 0; i < komoji.size(); i++)
        {
            cout << komoji[i];
        }
        for (int i = 0; i < oomoji.size(); i++)
        {
            cout << oomoji[i];
        }
        for (int i = 0; i < number.size(); i++)
        {
            cout << number[i];
        }
        cout << "\n";
    }
}