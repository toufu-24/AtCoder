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
    int N;
    cin >> N;
    vector<int> A(N * 3);
    for (int i = 0; i < N * 3; i++)
    {
        cin >> A[i];
    }
    vector<int> cnt(N + 1);
    for (int i = 0; i < N * 3; i++)
    {
        cnt[A[i]]++;
        if (cnt[A[i]] == 2)
        {
            cout << A[i] << " " << endl;
        }
    }
}