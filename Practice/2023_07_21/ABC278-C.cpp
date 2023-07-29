#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

int main()
{
    int N, Q;
    cin >> N >> Q;
    map<int, set<int>> FF;
    for (int q = 0; q < Q; q++)
    {
        int order;
        cin >> order;
        int a, b;
        switch (order)
        {
        case 1:
            cin >> a >> b;
            FF[--a].insert(--b);
            break;
        case 2:
            cin >> a >> b;
            FF[--a].erase(--b);
            break;
        case 3:
            cin >> a >> b;
            if (FF[--a].count(--b) && FF[b].count(a))
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
            break;
        }
    }
}