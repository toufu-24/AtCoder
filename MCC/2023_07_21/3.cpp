#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define sort(v) sort(v.begin(), v.end())
#define reverse(v) reverse(v.begin(), v.end())
#define ll int64_t

string umekomi[] = {"000", "008", "016", "024", "032", "040", "048", "056", "064", "072", "080", "088", "096", "104", "112", "120", "128", "136", "144", "152", "160", "168", "176", "184", "192", "200", "208", "216", "224", "232", "240", "248", "256", "264", "272", "280", "288", "296", "304", "312", "320", "328", "336", "344", "352", "360", "368", "376", "384", "392", "400", "408", "416", "424", "432", "440", "448", "456", "464", "472", "480", "488", "496", "504", "512", "520", "528", "536", "544", "552", "560", "568", "576", "584", "592", "600", "608", "616", "624", "632", "640", "648", "656", "664", "672", "680", "688", "696", "704", "712", "720", "728", "736", "744", "752", "760", "768", "776", "784", "792", "800", "808", "816", "824", "832", "840", "848", "856", "864", "872", "880", "888", "896", "904", "912", "920", "928", "936", "944", "952", "960", "968", "976", "984", "992"};

int main()
{
    string S;
    cin >> S;
    multiset<char> st;
    for (int i = 0; i < S.size(); i++)
    {
        st.insert(S[i]);
    }
    if (S.size() == 1)
    {
        int num = stoi(S);
        if (num % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << "No" << endl;
        return 0;
    }
    if (S.size() == 2)
    {
        int num = stoi(S);
        if (num % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        swap(S[0], S[1]);
        num = stoi(S);
        if (num % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << "No" << endl;
        return 0;
    }
    // 下3桁が8の倍数ならば、Sは8の倍数
    // -> 3桁の8の倍数の全ての要素が含まれていればよい
    for (int i = 0; i < 1000 / 8; i++)
    {
        multiset<char> st2 = st;
        string T = umekomi[i];
        int cnt = 0;
        for (int k = 0; k < T.size(); k++)
        {
            auto itr = st2.find(T[k]);
            if (itr != st2.end())
            {
                st2.erase(itr);
                cnt++;
            }
        }
        if (cnt == 3)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}