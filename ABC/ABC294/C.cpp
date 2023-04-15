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
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    vector<int> B(M);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int j = 0; j < M; j++)
    {
        cin >> B[j];
    }
    vector<int> A_ans(N);
    vector<int> B_ans(M);
    int a_cnt = 0;
    int b_cnt = 0;
    for (int i = 1; i <= N + M; i++)
    {
        if (b_cnt == M || (a_cnt < N && A[a_cnt] < B[b_cnt]))
        {
            A_ans[a_cnt] = i;
            a_cnt++;
        }
        else
        {
            B_ans[b_cnt] = i;
            b_cnt++;
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << A_ans[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < M; i++)
    {
        cout << B_ans[i] << " ";
    }
}