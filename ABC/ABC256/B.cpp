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
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int P = 0;
    bitset<4> base;
    for (int i = 0; i < N; i++)
    {
        base.set(0, 1);
        int moto = base.count();
        base <<= A[i];
        int ato = base.count();
        P += abs(moto - ato);
    }
    cout << P;
}