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
    string S, T;
    cin >> S >> T;
    multiset<char> s, t;
    for (auto c : S)
    {
        s.insert(c);
    }
    for (auto c : T)
    {
        t.insert(c);
    }
    set<char> atcoder;
    string at = "atcoder";
    for (int i = 0; i < 7; i++)
    {
        atcoder.insert(at[i]);
    }

    int s_at = s.count('@');
    int t_at = t.count('@');
    int sum = s_at + t_at;
    for (int i = 0; i < 26; i++)
    {
        if (atcoder.count(char('a' + i)))
        {
            if (s.count(char('a' + i)) == t.count(char('a' + i)))
            {
                continue;
            }
            else
            {
                sum -= abs(static_cast<int>(s.count(char('a' + i)) - t.count(char('a' + i))));
            }
            if (sum < 0)
            {
                cout << "No" << endl;
                return 0;
            }
        }
        else if (s.count(char('a' + i)) != t.count(char('a' + i)))
        {
            cout << "No" << endl;
            return 0;
        }
    }
    if (sum < 0)
    {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
}