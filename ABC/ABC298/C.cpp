#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<vector<int>> box(N);
    vector<set<int>> card(200001);
    for (int i = 0; i < Q; i++)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int x, y;
            cin >> x >> y;
            box[y - 1].push_back(x - 1);
            card[x - 1].insert(y - 1);
        }
        else if (q == 2)
        {
            int x;
            cin >> x;
            sort(box[x - 1]);
            for (auto val : box[x - 1])
            {
                cout << val + 1 << " ";
            }
            cout << "\n";
        }
        else if (q == 3)
        {
            int x;
            cin >> x;
            for (auto val : card[x - 1])
            {
                cout << val + 1 << " ";
            }
            cout << "\n";
        }
    }
}