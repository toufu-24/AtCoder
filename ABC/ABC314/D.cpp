#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    int last_order = 0;
    vector<pair<int, char>> changes;
    for (int q = 0; q < Q; q++)
    {
        int t, x;
        char c;
        cin >> t >> x >> c;
        switch (t)
        {
        case 1:
            S[x - 1] = c;
            changes.push_back({x - 1, c});
            break;
        default:
            last_order = t;
            changes.clear();
        }
    }
    switch (last_order)
    {
    case 2:
        for (int i = 0; i < N; i++)
        {
            if ('A' <= S[i] && S[i] <= 'Z')
            {
                S[i] = S[i] - 'A' + 'a';
            }
        }
        break;
    case 3:
        for (int i = 0; i < N; i++)
        {
            if ('a' <= S[i] && S[i] <= 'z')
            {
                S[i] = S[i] - 'a' + 'A';
            }
        }
        break;
    default:
        break;
    }
    for (int i = 0; i < changes.size(); i++)
    {
        S[changes[i].first] = changes[i].second;
    }
    cout << S;
}