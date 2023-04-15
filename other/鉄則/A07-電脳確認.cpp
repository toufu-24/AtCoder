#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int D, N;
    cin >> D >> N;
    vector<int> attendance(D, 0);
    vector<int> L(N);
    vector<int> R(N);
    for (int i = 0; i < N; i++)
    {
        cin >> L[i] >> R[i];
    }
    for (int i = 1; i <= D; i++)
    {
        int cnt = 0;
        for (int j = 0; j < N; j++)
        {
            if (L[j] <= i && i <= R[j])
            {
                cnt++;
            }
        }
        cout << cnt << endl;
    }
}