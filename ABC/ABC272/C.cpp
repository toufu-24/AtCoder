#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> even;
    vector<int> odd;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (A[i] % 2 == 0)
        {
            even.push_back(A[i]);
        }
        else
        {
            odd.push_back(A[i]);
        }
    }
    if (even.size() < 2 && odd.size() < 2)
    {
        cout << -1;
    }
    else if (even.size() >= 2 && odd.size() >= 2)
    {
        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());
        cout << max(even[even.size() - 1] + even[even.size() - 2], odd[odd.size() - 1] + odd[odd.size() - 2]);
    }
    else if (even.size() >= 2 && odd.size() < 2)
    {
        sort(even.begin(), even.end());
        cout << even[even.size() - 1] + even[even.size() - 2];
    }
    else if (even.size() < 2 && odd.size() >= 2)
    {
        sort(odd.begin(), odd.end());
        cout << odd[odd.size() - 1] + odd[odd.size() - 2];
    }
}