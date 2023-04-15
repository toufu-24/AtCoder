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
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A);
    int cnt = 0, ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        if (A[i] == A[i + 1])
        {
            ans++;
            i++;
        }
    }
    cout << ans;
}