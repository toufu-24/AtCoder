#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, K;
    cin >> N >> K;
    vector<string> S(K);
    for (int i = 0; i < K; i++)
    {
        cin >> S[i];
    }
    sort(S);
    for (int i = 0; i < K; i++)
    {
        cout << S[i] << endl;
    }
}