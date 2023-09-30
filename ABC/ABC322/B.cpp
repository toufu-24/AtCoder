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
    int N, M;
    cin >> N >> M;
    string S, T;
    cin >> S >> T;
    string forward_T, backward_T;
    forward_T = T.substr(0, N);
    backward_T = T.substr(M - N, N);
    cerr << forward_T << endl;
    cerr << backward_T << endl;
    if (forward_T == S && backward_T == S)
    {
        cout << 0;
    }
    else if (forward_T == S)
    {
        cout << 1;
    }
    else if (backward_T == S)
    {
        cout << 2;
    }
    else
    {
        cout << 3;
    }
}