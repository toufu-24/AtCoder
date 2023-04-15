#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int want_read = 1;
    int read = 0;
    for (int i = 0; true;)
    {
        if (a[i] != want_read)
        {
            if (a[a.size() - 1] != 0)
                a.pop_back();
            if (a.size() == 0)
            {
                break;
            }
            if (a[a.size() - 1] != 0)
                a.pop_back();
            read++;
        }
        else
        {
            read++;
            a.erase(a.begin());
        }
        if (a.size() == 0)
            break;
        want_read++;
    }
    cout << read << endl;
}