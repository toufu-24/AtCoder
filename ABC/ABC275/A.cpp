#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> H(N);
    for (int i = 0; i < N; i++)
    {
        cin >> H[i];
    }
    int ans = 1;
    int max = H[0];
    for (int i = 1; i < N; i++)
    {
        if (H[i] > max)
        {
            max = H[i];
            ans = i + 1;
        }
    }
    cout << ans;
}