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
    char p, q;
    cin >> p >> q;
    int dist[7] = {0, 3, 4, 8, 9, 14, 23};
    cout << abs(dist[int(p - 'A')] - dist[int(q - 'A')]);
}