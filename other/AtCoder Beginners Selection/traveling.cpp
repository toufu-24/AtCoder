#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> t(N);
    vector<int> x(N);
    vector<int> y(N);
    for (int i = 0; i < N; i++)
    {
        cin >> t[i] >> x[i] >> y[i];
    }
    bool flag = true;
    tuple<int, int, int> me(0, 0, 0);
    for (int i = 0; i < N; i++)
    {
        if ((abs(get<0>(me) - x[i]) + abs(get<1>(me) - y[i]) - (t[i] - get<2>(me))) % 2 != 0 || abs(get<0>(me) - x[i]) + abs(get<1>(me) - y[i]) > (t[i] - get<2>(me)))
        {
            flag = false;
            break;
        }
        me = make_tuple(x[i], y[i], t[i]);
    }
    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}