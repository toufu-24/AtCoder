#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, Q;
    cin >> N >> Q;
    int T[1000000000];
    int A[1000000000];
    int B[1000000000];
    set<int> follow_list[1000000000];
    for (int i = 1; i <= Q; i++)
    {
        cin >> T[i] >> A[i] >> B[i];
    }
    for (int i = 1; i <= Q; i++)
    {
        if (T[i] == 1)
            follow_list[A[i]].insert(B[i]);
        else if (T[i] == 2)
            follow_list[A[i]].erase(B[i]);
        else if (T[i] == 3)
            if (follow_list[A[i]].count(B[i]) && follow_list[B[i]].count(A[i]))
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
    }
}