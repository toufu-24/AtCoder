#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N;
    cin >> N;
    vector<int> P(N);
    vector<int> Q(N);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        Q[i] = P[i];
    }
    set<int> last;
    last.insert(P[N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        last.insert(P[i]);
        if (P[i + 1] - P[i] < 0)
        {
            int max = 0;
            for (int j = i + 1; j < N; j++)
            {
                if (P[i] - P[j] > 0 && P[j] > max)
                {
                    max = P[j];
                }
            }
            last.erase(max);
            Q[i] = max;
            vector<int> tmp;
            for (auto x : last)
            {
                tmp.push_back(x);
            }
            int cnt = 0;
            for (int j = i + 1; j < N; j++)
            {
                Q[j] = tmp[tmp.size() - cnt - 1];
                cnt++;
            }
            break;
        }
    }
    for (auto x : Q)
    {
        cout << x << " ";
    }
}
