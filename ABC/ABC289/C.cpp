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
    vector<set<int>> C(M);
    for (int i = 0; i < M; i++)
    {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++)
        {
            int tmp;
            cin >> tmp;
            C[i].insert(tmp);
        }
    }
    vector<set<int>> lost(M);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!C[i].count(j))
            {
                lost[i].insert(j);
            }
        }
    }
    int cnt = 0;
    int all = pow(2, M) - 1;
    int bit = 1;
    for (int i = 0; i < all; i++)
    {
        string r;
        int tmp = bit;
        while (tmp != 0)
        {
            r += (tmp % 2 == 0 ? "0" : "1");
            tmp /= 2;
        }
        set<int> Union;
        for (int j = 0; j < M; j++)
        {
            if (r[j] == '1')
            {
                for (auto x : C[j])
                {
                    Union.insert(x);
                }
            }
        }
        for (int j = 1; j <= N; j++)
        {
            if (!Union.count(j))
            {
                cnt++;
                break;
            }
        }
        bit++;
    }
    cout << all - cnt ;
}