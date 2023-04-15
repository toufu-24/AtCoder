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
    int N, P, Q, R, S;
    cin >> N >> P >> Q >> R >> S;
    vector<int> A(N);
    vector<int> B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        B[i] = A[i];
    }
    vector<int> tmp(N);
    for (int i = 0; i <= Q - P; i++)
    {
        B[i + P - 1] = A[i + R - 1];
        B[i + R - 1] = A[i + P - 1];
    }
    for (int i = 0; i < N; i++)
    {
        cout << B[i] << " ";
    }
}