#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    vector<int> look_right(N + 1);
    vector<int> look_left(N + 1);
    look_right[0] = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'W')
        {
            look_right[i] = look_right[i - 1] + 1;
        }
        else
        {
            look_right[i] = look_right[i - 1];
        }
    }
    look_left[N] = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (S[i] == 'E')
        {
            look_left[i] = look_left[i + 1] + 1;
        }
        else
        {
            look_left[i] = look_left[i + 1];
        }
    }

    int minimum = 1e9;
    for (int i = 0; i < N; i++)
    {
        minimum = min(minimum, look_right[i - 1] + look_left[i + 1]);
    }
    cout << minimum;
}