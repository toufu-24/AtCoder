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
    vector<int> tmp;
    for (int i = 1; i <= N; i++)
    {
        if (a.count(i))
        {
            tmp.push_back(i);
        }
        else
        {
            cout << i << " ";
            for (int j = tmp.size() - 1; j >= 0; j--)
            {
                cout << tmp[j] << " ";
            }
            tmp.clear();
        }
    }
}