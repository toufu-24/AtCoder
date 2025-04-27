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

// https://algo-logic.info/trie-tree/
/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(word): 単語 word を Trie 木に挿入する
    search(word): 単語 word が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
    count(): 挿入した単語の数を返す
    size(): Trie 木の頂点数を返す
    計算量：insert, search ともに O(M)（Mは単語の長さ）
*/
template <int char_size, int base>
struct Trie {
    struct Node {         // 頂点を表す構造体
        vector<int> next; // 子の頂点番号を格納。存在しなければ-1
        // int prefixes = 0;   // この頂点を使う単語の個数
        vector<int> accept; // 末端がこの頂点になる単語の word_id を保存
        int c;              // base からの間隔をint型で表現したもの
        int common;         // いくつの単語がこの頂点を共有しているか
        Node(int c_) : c(c_), common(0) {
            next.assign(char_size, -1);
        }
    };
    vector<Node> nodes; // trie 木本体
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }
    // 単語の挿入
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) { // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);
    }
    void insert(const string &word) {
        insert(word, nodes[0].common);
    }
    // 単語とprefixの検索
    bool search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) { // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }
    // prefix の検索(個数)
    int prefix_count(const string &prefix) {
        int node_id = 0;
        for (int i = 0; i < (int)prefix.size(); i++) {
            int c = (int)(prefix[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) { // 次の頂点が存在しなければ終了
                return 0;
            }
            node_id = next_id;
        }
        return nodes[node_id].common;
    }

    // prefix を持つ単語が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true);
    }
    // 挿入した単語の数
    int count() const {
        return (nodes[0].common);
    }
    // Trie木のノード数
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
            Xtrie.insert(s);
            debug_X.insert(s);
            // Yに含まれる文字列でprefixになっている個数ひく
            int cnt = Ytrie.prefix_count(s);
            ans -= cnt;
        } else {
            // sをYに追加
            Ytrie.insert(s);
            debug_Y.insert(s);
            // Xに含まれる文字列にprefixがあるか
            // あるならansを減らす
            bool exist = Xtrie.search(s, true);
            ans -= exist;
            ans++;
        }
        cout << ans << endl;
    }
}
