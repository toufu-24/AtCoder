#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int cnt = 0;
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; i++)
        {
            cin >> A[i];
            if (A[i] % 2 == 1)
            {
                cnt++;
            }
        }
        cout << cnt << endl;
    }
}