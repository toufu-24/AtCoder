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
    int N;
    cin >> N;
    int left = 2;
    int right = N - 1;
    for (int i = 0; i < 20; i++)
    {
        int mid = (left + right) / 2;
        cout << "? " << mid << endl;
        int res;
        cin >> res;
        if (res == 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
        if (right < left)
        {
            break;
        }
    }
    cout << "! " << right << endl;
}