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
    int N;
    cin >> N;
    vector<tuple<string, int, int>> vec(N);
    for (int i = 0; i < N; i++)
    {
        cin >> get<0>(vec[i]) >> get<1>(vec[i]);
        get<1>(vec[i]) *= -1;
        get<2>(vec[i]) = i + 1;
    }
    sort(vec);
    for (int i = 0; i < N; i++)
    {
        cout << get<2>(vec[i]) << endl;
    }
}