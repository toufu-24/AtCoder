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
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    vector<int> index(N);
    for (int i = 0; i < N; i++)
    {
        A[i] = i;
        index[i] = i;
    }
    vector<int> x(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> x[i];
        x[i]--;
        if (index[x[i]] != N - 1)
        {
            swap(A[index[x[i]]], A[index[x[i]] + 1]);
            index[A[index[x[i]]]]--;
            index[A[index[x[i]] + 1]]++;
        }
        else
        {
            swap(A[index[x[i]]], A[index[x[i]] - 1]);
            index[A[index[x[i]]]]++;
            index[A[index[x[i]] - 1]]--;
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << A[i] + 1<< " ";
    }
}