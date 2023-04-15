#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())

int main()
{
    int N, K;
    cin >> N >> K;
    queue<int> A;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        A.push(tmp);
    }
    for (int i = 0; i < K; i++)
    {
        A.pop();
        A.push(0);
    }
    while (!A.empty())
    {
        cout << A.front() << " ";
        A.pop();
    }
}