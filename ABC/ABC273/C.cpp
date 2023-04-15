#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(all(A));
    vector<int> memo(N, 1);
    memo[N - 1] = 0;
    int count = 0;
    for (int i = N - 2; i >= 0; i--)
    {
        if (A[i] != A[i + 1])
        {
            count++;
        }
        memo[i] = count;
    }
    reverse(all(memo));
    vector<int> ans(N);
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        int count2 = 0;
        bool flag = false;
        for (; j < N; j++)
        {
            if (i == memo[j])
            {
                count2++;
                flag = true;
            }
            else if (flag && i != memo[j])
            {
                ans[i] = count2;
                j--;
                break;
            }
        }
        ans[i] = count2;
    }
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << endl;
    }
}