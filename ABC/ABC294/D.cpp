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
    int N, Q;
    cin >> N >> Q;
    set<int> uncall_people;
    for (int i = 0; i < N; i++)
    {
        uncall_people.insert(i + 1);
    }
    set<int> called_people;
    for (int i = 0; i < Q; i++)
    {
        int num;
        cin >> num;
        if (num == 1)
        {
            called_people.insert(*begin(uncall_people));
            uncall_people.erase(*begin(uncall_people));
        }
        else if (num == 2)
        {
            int x;
            cin >> x;
            called_people.erase(x);
        }
        else
        {
            cout << *begin(called_people) << "\n";
        }
    }
}