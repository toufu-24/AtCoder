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
    int N, A, B;
    cin >> N >> A >> B;
    string S;
    cin >> S;
    int sum = 0;
    int foreign = 0;
    for (int i = 0; i < N; i++)
    {
        switch (S[i])
        {
        case 'a':
            if (sum < A + B)
            {
                cout << "Yes" << endl;
                sum++;
            }
            else
            {
                cout << "No" << endl;
            }
            break;
        case 'b':
            if (sum < A + B && foreign < B)
            {
                cout << "Yes" << endl;
                sum++;
                foreign++;
            }
            else
            {
                cout << "No" << endl;
            }
            break;
        case 'c':
            cout << "No" << endl;
            break;
        }
    }
}