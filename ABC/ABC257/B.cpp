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
    int N, K, Q;
    cin >> N >> K >> Q;
    vector<bool> mass(N, false);
    vector<int> A(K);
    for (int i = 0; i < K; i++)
    {
        cin >> A[i];
        A[i]--;
        mass[A[i]] = true;
    }
    vector<int> L(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> L[i];
        L[i]--;
        if (A[L[i]] != N - 1 && !mass[A[L[i]] + 1])
        {
            mass[A[L[i]]] = false;
            mass[A[L[i]] + 1] = true;
            A[L[i]]++;
        }
    }
    for (int i = 0; i < K; i++)
    {
        cout << A[i] + 1 << " ";
    }
}