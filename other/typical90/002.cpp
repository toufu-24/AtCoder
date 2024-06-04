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

int32_t main()
{
    int N;
    cin >> N;
    if (N % 2 == 1)
    {
        return 0;
    }
    vector<char> parentheses;
    for (int i = 0; i < N / 2; i++)
    {
        parentheses.push_back('(');
    }
    for (int i = 0; i < N / 2; i++)
    {

        parentheses.push_back(')');
    }

    do
    {
        bool ok = true;
        stack<char> st;
        for (int i = 0; i < N; i++)
        {
            if (parentheses[i] == '(')
            {
                st.push(parentheses[i]);
            }
            else
            {
                if (st.empty())
                {
                    ok = false;
                    break;
                }
                st.pop();
            }
        }
        if (ok && st.empty())
        {
            for (int i = 0; i < N; i++)
            {
                cout << parentheses[i];
            }
            cout << endl;
        }
    } while (next_permutation(all(parentheses)));
}
