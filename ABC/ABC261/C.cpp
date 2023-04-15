#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<string> S(N);
    map<string, int> count;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        count[S[i]] = count[S[i]] + 1;
        if (count[S[i]] != 1)
        {
            cout << S[i] << "(" << count[S[i]] - 1 << ")" << endl;
        }
        else
        {
            cout << S[i] << endl;
        }
    }
}