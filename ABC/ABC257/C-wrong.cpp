#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t
#define ld long double

ll calc_correct(vector<int> &child, vector<int> &adult, ld judge)
{
    ll child_size = child.size();
    ll adult_size = adult.size();
    ll adult_correct = adult_size - (lower_bound(all(adult), judge) - adult.begin());
    ll child_correct = lower_bound(all(child), judge) - child.begin();
    return adult_correct + child_correct;
}

int main()
{
    int N;
    cin >> N;
    string S;
    cin >> S;
    vector<int> child;
    vector<int> adult;
    vector<int> W(N);
    for (int i = 0; i < N; i++)
    {
        cin >> W[i];
        if (S[i] == '1')
        {
            adult.push_back(W[i]);
        }
        else
        {
            child.push_back(W[i]);
        }
    }
    sort(child);
    sort(adult);
    int child_size = child.size();
    int adult_size = adult.size();

    // 三分探索
    ld right = 1e9;
    ld left = -1;
    ll max_correct = 0;
    while (left + 2 < right)
    {
        ld c1 = (left * 2 + right) / 3;
        ld c2 = (left + right * 2) / 3;
        ld correct_sum1 = calc_correct(child, adult, c1);
        ld correct_sum2 = calc_correct(child, adult, c2);

        if (correct_sum1 >= correct_sum2)
        {
            right = c2;
        }
        else
        {
            left = c1;
        }
    }
    ll left2 = floor(left);
    max_correct = calc_correct(child, adult, left2 - 1);
    for (int i = left2; i <= ceil(right); i++)
    {
        max_correct = max(max_correct, calc_correct(child, adult, i));
    }

    cout << max_correct << endl;
}