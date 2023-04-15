#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())

vector<int> H(1);
vector<int> W(2);

int main()
{
    int N;
    cin >> N;
    int x, y;
    cin >> x >> y;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    H[0] = 0;
    W[0] = A[0];

    for (int i = 1; i < N; i++)
    {
        //奇数なら縦
        if (i % 2 == 1)
        {
            int cnt = 0;
            for (int j = 0; j < pow(2, (i / 2) - 1); j++)
            {
                H.push_back(H[H.size() - 1 - j - cnt] + A[i]);
                H.push_back(H[H.size() - 2 - j - cnt] - A[i]);
                cnt += 2;
            }
        }
        //偶数なら横
        else
        {
            int cnt = 0;
            for (int j = 0; j < pow(2, (i / 2)); j++)
            {
                W.push_back(W[W.size() - 1 - j - cnt] + A[i]);
                W.push_back(W[W.size() - 2 - j - cnt] - A[i]);
                cnt += 2;
            }
        }
    }
    bool H_flag = false;
    bool W_flag = false;
    for (int i = 0; i < pow(2, N); i++)
    {
        if (H[H.size() - 1 - i] == y)
        {
            H_flag = true;
            break;
        }
    }
    for (int i = 0; i < pow(2, N - 1); i++)
    {
        if (W[W.size() - 1 - i] == x)
        {
            W_flag = true;
            break;
        }
    }

    if (H_flag && W_flag)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}
