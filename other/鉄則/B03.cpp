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
    bool ans = false;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            for (int k = j + 1; k < N; k++)
            {
                if (A[i] + A[j] + A[k] == 1000)
                {
                    ans = true;
                    goto loop;
                }
            }
        }
    }
loop:
    if (ans)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}