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
    string S;
    cin >> S;
    SORT(S);

    vector<ll> square_number;
    for (ll i = 0; i * i < 1e13 + 100; i++)
    {
        square_number.push_back(i * i);
    }

    ll cnt = 0;
    for (int i = 0; i < square_number.size(); i++)
    {
        string s = to_string(square_number[i]);
        SORT(s);
        while (s.size() < S.size())
        {
            s = '0' + s;
        }

        if (s == S)
        {
            cnt++;
        }
    }
    cout << cnt << endl;
}