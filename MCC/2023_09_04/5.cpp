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
    vector<int> odd_A, even_A;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (i % 2 == 0)
        {
            even_A.push_back(A[i]);
        }
        else
        {
            odd_A.push_back(A[i]);
        }
    }
    sort(even_A);
    sort(odd_A);
    A.clear();
    for (int i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            A.push_back(even_A[i / 2]);
        }
        else
        {
            A.push_back(odd_A[i / 2]);
        }
    }
    int ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        if (A[i] > A[i + 1])
        {
            ans++;
            swap(A[i], A[i + 1]);
        }
    }

    cout << ans << endl;
}