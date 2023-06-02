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
    int N, A, B;
    cin >> N >> A >> B;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        if (C[i] == A + B)
        {
            cout << i+1;
            return 0;
        }
    }
}