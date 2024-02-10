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
    string A, B, C;
    cin >> A >> B >> C;
    queue<char> a, b, c;
    for (int i = 0; i < A.size(); i++)
    {
        a.push(A[i]);
    }
    for (int i = 0; i < B.size(); i++)
    {
        b.push(B[i]);
    }
    for (int i = 0; i < C.size(); i++)
    {
        c.push(C[i]);
    }

    char turn = 'a';
    while (true)
    {
        if (turn == 'a')
        {
            if (a.empty())
            {
                cout << "A" << endl;
                return 0;
            }
            turn = a.front();
            a.pop();
        }
        else if (turn == 'b')
        {
            if (b.empty())
            {
                cout << "B" << endl;
                return 0;
            }
            turn = b.front();
            b.pop();
        }
        else
        {
            if (c.empty())
            {
                cout << "C" << endl;
                return 0;
            }
            turn = c.front();
            c.pop();
        }
    }
}