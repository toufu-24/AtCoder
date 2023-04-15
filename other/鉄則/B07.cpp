#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int T, N;
    cin >> T >> N;
    vector<int> L(N);
    vector<int> R(N);
    for (int i = 0; i < N; i++)
    {
        cin >> L[i] >> R[i];
    }
    vector<int> increase_decrease(T, 0);
    for (int i = 0; i < N; i++)
    {
        increase_decrease[L[i]]++;
        increase_decrease[R[i]]--;
    }
    vector<int> how_many(T, 0);
    how_many[0] = increase_decrease[0];
    for (int i = 1; i < T; i++)
    {
        how_many[i] = how_many[i - 1] + increase_decrease[i];
    }
    for (int i = 0; i < T; i++)
    {
        cout << how_many[i] << endl;
    }
}