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
    int H, W, N;
    cin >> H >> W >> N;
    vector<pair<int, int>> cards(N);
    for (int i = 0; i < N; i++)
    {
        cin >> cards[i].first >> cards[i].second;
    }
}