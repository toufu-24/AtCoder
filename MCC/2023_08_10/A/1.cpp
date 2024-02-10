#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    set<char> S;
    for (int i = 0; i < N; i++)
    {
        char tmp;
        cin >> tmp;
        S.insert(tmp);
    }
    if (S.size() == 3)
    {
        cout << "Three" << endl;
    }
    else
    {
        cout << "Four" << endl;
    }
}