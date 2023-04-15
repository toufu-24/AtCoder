#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<pair<int, int>> num(N);
    for (size_t i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        num.at(i).second = tmp;
        cin >> tmp;
        num.at(i).first = tmp;
    }

    sort(num.begin(), num.end());

    for (size_t i = 0; i < N; i++)
    {
        cout << num.at(i).second << " " << num.at(i).first << endl;
    }
}