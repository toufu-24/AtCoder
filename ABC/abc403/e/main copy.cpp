#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

#define all(v) v.begin(), v.end()
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())
#define ll long
#define ld long double

#define int ll

template <int char_size>
struct TrieNode {
    int nxt[char_size];

    int exist;
    vector<int> accept;

    TrieNode() : exist(0) {
        memset(nxt, -1, sizeof(nxt));
    }
};

template <int char_size, int margin>
struct Trie {
    using Node = TrieNode<char_size>;

    vector<Node> nodes;
    int root;

    Trie() : root(0) {
        nodes.push_back(Node());
    }

    void update_direct(int node, int id) {
        nodes[node].accept.push_back(id);
    }

    void update_child(int node, int child, int id) {
        ++nodes[node].exist;
    }

    void add(const string &str, int str_index, int node_index, int id) {
        if (str_index == str.size()) {
            update_direct(node_index, id);
        } else {
            const int c = str[str_index] - margin;
            if (nodes[node_index].nxt[c] == -1) {
                nodes[node_index].nxt[c] = (int)nodes.size();
                nodes.push_back(Node());
            }
            add(str, str_index + 1, nodes[node_index].nxt[c], id);
            update_child(node_index, nodes[node_index].nxt[c], id);
        }
    }

    void add(const string &str, int id) {
        add(str, 0, 0, id);
    }

    void add(const string &str) {
        add(str, nodes[0].exist);
    }

    void query(const string &str, const function<void(int)> &f, int str_index, int node_index) {
        for (auto &idx : nodes[node_index].accept)
            f(idx);
        if (str_index == str.size()) {
            return;
        } else {
            const int c = str[str_index] - margin;
            if (nodes[node_index].nxt[c] == -1)
                return;
            query(str, f, str_index + 1, nodes[node_index].nxt[c]);
        }
    }

    void query(const string &str, const function<void(int)> &f) {
        query(str, f, 0, 0);
    }

    int count() const {
        return (nodes[0].exist);
    }

    int size() const {
        return ((int)nodes.size());
    }
};

int32_t main() {
    int q;
    cin >> q;
    set<string> debug_X, debug_Y;
    Trie<26, 'a'> Ytrie, Xtrie;
    int ans = 0;
    while (q--) {
        int t;
        string s;
        cin >> t >> s;
        if (t == 1) {
            // sをXに追加
            Xtrie.add(s);
            debug_X.insert(s);
            // Yに含まれる文字列でprefixになっている個数ひく
            int cnt = 0;
            Ytrie.query(s, [&](int id) { cnt++; });
            ans -= cnt;
        } else {
            // sをYに追加
            Ytrie.add(s);
            debug_Y.insert(s);
            // Xに含まれる文字列にprefixがあるか
            // あるならansを減らす
            int cnt = 0;
            Xtrie.query(s, [&](int id) { cnt++; });
            ans -= (cnt > 0);
            ans++;
        }
        cout << ans << endl;
    }
}
