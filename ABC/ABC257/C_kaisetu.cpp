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
    string S;
    cin >> S;
    int ans = 0;
    vector<pair<int, char>> people(N);
    for (int i = 0; i < N; i++)
    {
        cin >> people[i].first;
        people[i].second = S[i];
        if (S[i] == '1')
            ans++;
    }
    sort(people);

    int x = ans;
    for (int i = 0; i < N; i++)
    {
        if (people[i].second == '1')
            x--;
        else
            x++;
        if (i == N - 1)
            ans = max(ans, x);
        else if (people[i].first != people[i + 1].first)
            ans = max(ans, x);
    }
    cout << ans << endl;
}