#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int main()
{
    int N;
    cin >> N;
    bitset<200000> S, T;
    cin >> S >> T;
    string U;
    string tmp = (S ^ T).to_string();
    string XOR = tmp.substr(tmp.size() - N, tmp.size() - 1);
    string XOR_1;
    for (int i = 0; i < N; i++)
    {
        if (XOR[i] == '1')
        {
            XOR_1 += to_string(i);
        }
    }
    if (XOR_1.size() % 2 == 1)
    {
        cout << -1 << endl;
        return 0;
    }
    tmp = S.to_string();
    string S2 = tmp.substr(tmp.size() - N, tmp.size() - 1);
    vector<int> place_0;
    vector<int> place_1;
    for (int i = 0; i < N; i++)
    {
        if (XOR[i] == '1' && S2[i] == '0')
        {
            place_0.push_back(i);
        }
        else if (XOR[i] == '1' && S2[i] == '1')
        {
            place_1.push_back(i);
        }
    }
    for (int i = 0; i < N; i++)
    {
        U += '0';
    }
    int num = (XOR_1.size() / 2) - place_0.size();
    num = abs(num);
    int num2 = (XOR_1.size() / 2) - place_1.size();
    num2 = abs(num2);
    if (place_0.size() > place_1.size())
    {
        for (int i = 0; i < num; i++)
        {
            U[place_0[place_0.size() - i - 1]] = '1';
        }
    }
    else if (place_0.size() < place_1.size())
    {
        for (int i = 0; i < num2; i++)
        {
            U[place_1[place_1.size() - i - 1]] = '1';
        }
    }
    cout << U << endl;
    return 0;
}