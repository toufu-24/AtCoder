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
    vector<vector<pair<int, int>>> info(N);
    for (int i = 0; i < N; i++)
    {
        int A;
        cin >> A;
        for (int j = 0; j < A; j++)
        {
            int x, y;
            cin >> x >> y;
            info[i].push_back(make_pair(x - 1, y));
        }
    }
}