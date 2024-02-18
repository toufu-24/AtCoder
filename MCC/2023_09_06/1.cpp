#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, L;
    cin >> N >> L;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    vector<bool> seat(L, false);
    int last = -1;
    int i = 0;
    for (i = 0; i < N; i++)
    {
        last += 2;
        if (a[i] == 1)
        {
            if (last >= L)
            {
                break;
            }
            seat[last] = true;
        }
        else
        {
            if (last == L - 1)
            {
                i++;
                break;
            }
            else if (last >= L)
            {
                break;
            }

            seat[last++] = true;
            seat[last] = true;
        }
    }
    for (; i < N; i++)
    {
        if (a[i] == 2)
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}