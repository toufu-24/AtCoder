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
    int N, M;
    cin >> N >> M;
    set<int> a;
    for (int i = 0; i < M; i++)
    {
        int tmp;
        cin >> tmp;
        a.insert(tmp);
    }
    vector<int> num(N + 1);
    for (int i = 1; i <= N; i++)
    {
        num[i] = i;
    }
    bool flag = false;
    for (int i = N - 1; i >= 1; i--)
    {
        if (a.count(i))
        {
            if (flag)
            {
                
            }
            else
            {
                int tmp = num[i];
                num[i] = num[i + 1];
                num[i + 1] = tmp;
            }
            flag = true;
        }
        else
        {
            flag = false;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        cout << num[i] << " ";
    }
}