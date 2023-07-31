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
    vector<int> sorted(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        sorted[i] = A[i];
    }
    sort(sorted);
    sorted.erase(unique(all(sorted)), sorted.end());
    for (int i = 0; i < N; i++)
    {
        cout << lower_bound(all(sorted), A[i]) - sorted.begin() + 1 << " ";
    }
}