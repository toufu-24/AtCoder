#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> cnt(2 * N + 1, 0);
    for (int i = 1; i <= N; i++)
    {
        int num = cnt[A[i - 1]];
        cnt[2 * i] = cnt[A[i - 1]] + 1;
        cnt[2 * i + 1] = cnt[A[i - 1]] + 1;
    }
    for (int i = 1; i <= 2 * N + 1; i++)
    {
        cout << cnt[i] << endl;
    }
}