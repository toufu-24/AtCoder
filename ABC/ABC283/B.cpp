#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        int num;
        cin >> num;
        if (num == 1)
        {
            int k, x;
            cin >> k >> x;
            A[k - 1] = x;
        }
        else
        {
            int k;
            cin >> k;
            cout << A[k - 1] << endl;
        }
    }
}