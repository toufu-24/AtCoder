#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.begin(), v.end(), greater<int>())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

#define int ll

int32_t main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    list<int> l;
    l.insert(l.end(), 0);
    auto itr = l.begin();
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'L')
        {
            l.insert(itr, i + 1);
            itr--;
        }
        else
        {
            itr++;
            l.insert(itr, i + 1);
            itr--;
        }
    }
    for (auto i : l)
    {
        cout << i << " ";
    }
}