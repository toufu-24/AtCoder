#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double


// https://rsk0315.hatenablog.com/entry/2020/10/11/125049
struct nekoset
{
private:
    std::set<std::pair<int, int>> s;

public:
    nekoset()
    {
        s.emplace(INT_MIN, INT_MIN);
        s.emplace(INT_MAX, INT_MAX);
    }

    bool contains(int x) const
    {
        auto it = std::prev(s.lower_bound(std::make_pair(x + 1, x + 1)));
        auto [l, u] = *it;
        return l <= x && x <= u;
    }

    bool erase(int x)
    {
        auto it = std::prev(s.lower_bound(std::make_pair(x + 1, x + 1)));
        auto [l, u] = *it;

        if (!(l <= x && x <= u))
            return false; // Element not found, cannot erase

        s.erase(it);

        // Check if we need to update the set with split or merge
        if (l < x)
        {
            s.emplace(l, x - 1);
        }
        if (u > x)
        {
            s.emplace(x + 1, u);
        }

        return true;
    }

    bool insert(int x)
    {
        auto nit = s.lower_bound(std::make_pair(x + 1, x + 1));
        auto it = std::prev(nit);
        auto [l, u] = *it;
        auto [nl, nu] = *nit;
        if (l <= x && x <= u)
            return false;
        if (u == x - 1)
        {
            if (nl == x + 1)
            {
                s.erase(it);
                s.erase(nit);
                s.emplace(l, nu);
            }
            else
            {
                s.erase(it);
                s.emplace(l, x);
            }
        }
        else
        {
            if (nl == x + 1)
            {
                s.erase(nit);
                s.emplace(x, nu);
            }
            else
            {
                s.emplace(x, x);
            }
        }
        return true;
    }

    int mex(int x = 0) const
    {
        auto [l, u] = *std::prev(s.lower_bound(std::make_pair(x + 1, x + 1)));
        if (l <= x && x <= u)
        {
            return u + 1;
        }
        else
        {
            return x;
        }
    }
};

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    nekoset s;
    for (int i = 0; i < N; i++)
    {
        s.insert(A[i]);
    }

    for (int q = 0; q < Q; q++)
    {
        int i, x;
        cin >> i >> x;
        i--;
        s.erase(A[i]);
        A[i] = x;
        s.insert(A[i]);
        cout << s.mex() << endl;
    }
}