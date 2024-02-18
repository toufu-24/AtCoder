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
    int N, K;
    cin >> N >> K;
    vector<pair<int, int>> zahyou(N);
    for (int i = 0; i < N; i++)
    {
        cin >> zahyou[i].first >> zahyou[i].second;
    }
    sort(zahyou);
    
}