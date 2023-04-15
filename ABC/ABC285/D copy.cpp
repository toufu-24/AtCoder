#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>
using namespace std;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll long long

struct HashPair
{

    static size_t m_hash_pair_random;

    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {

        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);

        size_t seed = 0;
        seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= m_hash_pair_random + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

size_t HashPair::m_hash_pair_random = (size_t)random_device()();

int main()
{
    double start = clock();
    int N;
    cin >> N;
    vector<string> S(N);
    vector<string> T(N);
    unordered_set<pair<string, string>, int, HashPair> S_set;
    unordered_set<string> S_only_set;
    for (int i = 0; i < N; i++)
    {
        cin >> S[i] >> T[i];
        S_set.insert(make_pair(S[i], T[i]));
        S_only_set.insert(S[i]);
    }
    bool flag = false;
    int cnt = 0;
    while (double(clock() - start) / CLOCKS_PER_SEC < 1.93)
    {
        for (pair<string, string> x : S_set)
        {
            if (S_only_set.count(x.second))
            {
                continue;
            }
            else
            {
                S_set.erase(x);
                S_only_set.erase(x.first);
                S_only_set.insert(x.second);
                cnt++;
            }
        }
        if (cnt == N)
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}