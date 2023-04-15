#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> T(Q + 10);
    vector<int> A(Q + 10);
    vector<int> B(Q + 10);
    for (int i = 1; i <= Q; i++)
    {
        cin >> T[i] >> A[i] >> B[i];
    }
    vector<set<int>> follow_list(N + 10);
    for (int i = 1; i <= Q; i++)
    {
        switch (T[i])
        {
        case 1:
            follow_list[A[i]].insert(B[i]);
            break;
        case 2:
            follow_list[A[i]].erase(B[i]);
            break;
        case 3:
            if (follow_list[A[i]].count(B[i]) && follow_list[B[i]].count(A[i]))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
            break;
        }
    }
}