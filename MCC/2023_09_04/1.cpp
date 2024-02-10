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
    int N;
    cin >> N;
    vector<int> a(N);
    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    while (mp.size() != 1)
    {
        int min = (*begin(mp)).first;
        int max = (*rbegin(mp)).first;
        mp[max - min] += mp[max];
        mp.erase(max);
    }
    cout << (*begin(mp)).first << endl;
}