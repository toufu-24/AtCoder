#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N;
    string S;
    cin >> N >> S;
    set<pair<int, int>> coo;
    int x = 0, y = 0;
    bool ans = false;
    for (int i = 0; i < N; i++)
    {
        pair<int, int> p(x, y);
        if (coo.count(p))
        {
            ans = true;
            break;
        }
        coo.insert(p);
        if (S[i] == 'R')
        {
            x++;
        }
        else if (S[i] == 'L')
        {
            x--;
        }
        else if (S[i] == 'U')
        {
            y++;
        }
        else if (S[i] == 'D')
        {
            y--;
        }
    }
    pair<int, int> p(x, y);
    if (coo.count(p))
    {
        ans = true;
    }
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}