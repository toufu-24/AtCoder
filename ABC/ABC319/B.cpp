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
    vector<int> yakusuu;
    for (int i = 1; i <= 9; i++)
    {
        if (N % i == 0)
        {
            yakusuu.push_back(i);
        }
    }
    int size = yakusuu.size();
    for (int i = 0; i <= N; i++)
    {
        bool exist = false;
        for (int j = 0; j < size; j++)
        {
            if (i % (N / yakusuu[j]) == 0)
            {
                cout << yakusuu[j];
                exist = true;
                break;
            }
        }
        if (exist == false)
        {
            cout << "-";
        }
    }
}